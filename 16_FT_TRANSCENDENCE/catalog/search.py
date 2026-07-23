from __future__ import annotations

import re
from collections.abc import Callable
from dataclasses import dataclass
from typing import Literal

from sqlalchemy import select
from sqlalchemy.orm import Session, selectinload

from models import Book, BookCategory
from pydantic import BaseModel


SearchField = Literal["title", "author", "category", "publisher", "description"]
SearchResultType = Literal["book", "author", "publisher", "genre"]
CatalogSearchFilter = SearchResultType


class SearchResult(BaseModel):
    id: int
    result_type: SearchResultType
    title: str
    author_name: str
    matched_field: SearchField
    matched_text: str


@dataclass(frozen=True)
class SearchEntry:
    book_id: int
    title: str
    author_name: str
    field: SearchField
    text: str
    normalized_text: str
    entity_id: int | None = None
    entity_name: str | None = None


@dataclass
class Candidate:
    entry: SearchEntry
    score: int


class TrieNode:
    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.entries: list[SearchEntry] = []


class SearchTrie:
    def __init__(self) -> None:
        self.root = TrieNode()

    def insert(self, key: str, entry: SearchEntry) -> None:
        node = self.root
        for char in key:
            node = node.children.setdefault(char, TrieNode())
        node.entries.append(entry)

    def prefix_matches(self, prefix: str, limit: int) -> list[SearchEntry]:
        node = self.root
        for char in prefix:
            if char not in node.children:
                return []
            node = node.children[char]

        matches: list[SearchEntry] = []
        stack = [node]
        while stack and len(matches) < limit:
            current = stack.pop()
            matches.extend(current.entries[: limit - len(matches)])
            stack.extend(current.children.values())
        return matches


FIELD_WEIGHT: dict[SearchField, int] = {
    "title": 50,
    "author": 35,
    "category": 25,
    "publisher": 20,
    "description": 10,
}


def normalize_search_text(value: str) -> str:
    return re.sub(r"\s+", " ", re.sub(r"[^a-z0-9]+", " ", value.lower())).strip()


def search_books(
    db: Session,
    query: str,
    limit: int = 6,
    result_type: CatalogSearchFilter | None = None,
) -> list[SearchResult]:
    normalized_query = normalize_search_text(query)
    if not normalized_query:
        return []

    limit = max(1, min(limit, 50))
    entries = _catalog_entries(db)
    if result_type is not None:
        return _search_filtered_entries(entries, normalized_query, limit, result_type)

    trie = SearchTrie()
    for entry in entries:
        trie.insert(entry.normalized_text, entry)

    candidates = _rank_candidates(trie, entries, normalized_query, limit)
    if not candidates:
        return []

    book_limit = limit
    results: list[SearchResult] = []
    if candidates[0].entry.field in ("author", "category", "publisher"):
        results.append(_entity_result(candidates[0].entry))
        book_limit -= 1

    results.extend([
        SearchResult(
            id=candidate.entry.book_id,
            result_type="book",
            title=candidate.entry.title,
            author_name=candidate.entry.author_name,
            matched_field=candidate.entry.field,
            matched_text=candidate.entry.text,
        )
        for candidate in candidates[:book_limit]
    ])
    return results


def _rank_candidates(
    trie: SearchTrie,
    entries: list[SearchEntry],
    normalized_query: str,
    limit: int,
    key_for_entry: Callable[[SearchEntry], int] = lambda entry: entry.book_id,
) -> list[Candidate]:
    prefix_entries = trie.prefix_matches(normalized_query, limit * 12)
    scored: dict[int, Candidate] = {}

    for entry in prefix_entries:
        _keep_best(
            scored,
            key_for_entry(entry),
            entry,
            _score_entry(entry, normalized_query, prefix_match=True),
        )

    if len(scored) < limit:
        for entry in entries:
            if normalized_query in entry.normalized_text:
                _keep_best(
                    scored,
                    key_for_entry(entry),
                    entry,
                    _score_entry(entry, normalized_query, prefix_match=False),
                )

    return sorted(
        scored.values(),
        key=lambda candidate: (
            -candidate.score,
            (candidate.entry.entity_name or candidate.entry.title).lower(),
            candidate.entry.book_id,
        ),
    )[:limit]


def _score_entry(entry: SearchEntry, normalized_query: str, prefix_match: bool) -> int:
    text = entry.normalized_text
    score = FIELD_WEIGHT[entry.field]

    if text == normalized_query:
        score += 100
    elif prefix_match:
        score += 75
    elif any(word.startswith(normalized_query) for word in text.split()):
        score += 60
    else:
        score += 25

    score += max(0, 30 - abs(len(text) - len(normalized_query)))
    return score


def _keep_best(scored: dict[int, Candidate], key: int, entry: SearchEntry, score: int) -> None:
    current = scored.get(key)
    if current is None or score > current.score:
        scored[key] = Candidate(entry=entry, score=score)


def _search_filtered_entries(
    entries: list[SearchEntry],
    normalized_query: str,
    limit: int,
    result_type: CatalogSearchFilter,
) -> list[SearchResult]:
    if result_type == "book":
        searchable_entries = entries
        result_builder = _book_result

        def key_for_entry(entry: SearchEntry) -> int:
            return entry.book_id
    else:
        field_by_type: dict[SearchResultType, SearchField] = {
            "author": "author",
            "publisher": "publisher",
            "genre": "category",
            "book": "title",
        }
        searchable_entries = [entry for entry in entries if entry.field == field_by_type[result_type]]
        result_builder = _entity_result

        def key_for_entry(entry: SearchEntry) -> int:
            return entry.entity_id or entry.book_id

    trie = SearchTrie()
    for entry in searchable_entries:
        trie.insert(entry.normalized_text, entry)

    return [
        result_builder(candidate.entry)
        for candidate in _rank_candidates(
            trie,
            searchable_entries,
            normalized_query,
            limit,
            key_for_entry=key_for_entry,
        )
    ]


def _book_result(entry: SearchEntry) -> SearchResult:
    return SearchResult(
        id=entry.book_id,
        result_type="book",
        title=entry.title,
        author_name=entry.author_name,
        matched_field=entry.field,
        matched_text=entry.text,
    )


def _catalog_entries(db: Session) -> list[SearchEntry]:
    categories_by_id = {category.id: category for category in db.scalars(select(BookCategory)).all()}
    books = db.scalars(
        select(Book)
        .where(Book.product_status == "active")
        .options(
            selectinload(Book.author),
            selectinload(Book.publisher),
            selectinload(Book.categories),
            selectinload(Book.translations),
        )
    ).all()

    entries: list[SearchEntry] = []
    for book in books:
        title = _display_title(book)
        author_name = book.author.author_name if book.author else "Unknown author"

        for translation in book.translations:
            _append_entry(entries, book.id, title, author_name, "title", translation.title)
            if translation.description:
                for token in _description_tokens(translation.description):
                    _append_entry(entries, book.id, title, author_name, "description", token)

        if book.author:
            _append_entry(
                entries,
                book.id,
                title,
                author_name,
                "author",
                author_name,
                entity_id=book.author.id,
                entity_name=author_name,
            )

        if book.publisher:
            _append_entry(
                entries,
                book.id,
                title,
                author_name,
                "publisher",
                book.publisher.publisher_name,
                entity_id=book.publisher.id,
                entity_name=book.publisher.publisher_name,
            )

        for category in book.categories:
            root_category = _root_category(category, categories_by_id)
            _append_entry(
                entries,
                book.id,
                title,
                author_name,
                "category",
                category.category_name,
                entity_id=root_category.id,
                entity_name=root_category.category_name,
            )

    return entries


def _append_entry(
    entries: list[SearchEntry],
    book_id: int,
    title: str,
    author_name: str,
    field: SearchField,
    text: str,
    entity_id: int | None = None,
    entity_name: str | None = None,
) -> None:
    normalized_text = normalize_search_text(text)
    if not normalized_text:
        return
    entries.append(
        SearchEntry(
            book_id=book_id,
            title=title,
            author_name=author_name,
            field=field,
            text=text,
            normalized_text=normalized_text,
            entity_id=entity_id,
            entity_name=entity_name,
        )
    )


def _entity_result(entry: SearchEntry) -> SearchResult:
    if entry.field == "author":
        return SearchResult(
            id=entry.entity_id or entry.book_id,
            result_type="author",
            title=entry.entity_name or entry.text,
            author_name="Author",
            matched_field=entry.field,
            matched_text=entry.text,
        )

    if entry.field == "publisher":
        return SearchResult(
            id=entry.entity_id or entry.book_id,
            result_type="publisher",
            title=entry.entity_name or entry.text,
            author_name="Publisher",
            matched_field=entry.field,
            matched_text=entry.text,
        )

    return SearchResult(
        id=entry.entity_id or entry.book_id,
        result_type="genre",
        title=entry.entity_name or entry.text,
        author_name="Genre",
        matched_field=entry.field,
        matched_text=entry.text,
    )


def _root_category(category: BookCategory, categories_by_id: dict[int, BookCategory]) -> BookCategory:
    current = category
    seen: set[int] = set()
    while current.parent_id and current.parent_id not in seen:
        seen.add(current.id)
        parent = categories_by_id.get(current.parent_id)
        if parent is None:
            break
        current = parent
    return current


def _display_title(book: Book) -> str:
    english = next((translation.title for translation in book.translations if translation.lang == "en"), None)
    return english or (book.translations[0].title if book.translations else f"Book #{book.id}")


def _description_tokens(description: str) -> list[str]:
    words = normalize_search_text(description).split()
    return [word for word in words if len(word) >= 3]
