import datetime
from typing import Optional

from sqlalchemy import (
    BigInteger,
    String,
    DateTime,
    ForeignKey,
    Numeric,
    Text,
    PrimaryKeyConstraint,
    SmallInteger,
    UniqueConstraint,
    func,
)
from sqlalchemy.orm import Mapped, mapped_column, relationship
from database import Base


class Author(Base):
    __tablename__ = "author"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    author_name: Mapped[str] = mapped_column(Text, nullable=False)


class Publisher(Base):
    __tablename__ = "publisher"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    publisher_name: Mapped[str] = mapped_column(Text, nullable=False)


class PublisherFollower(Base):
    __tablename__ = "publisher_followers"
    __table_args__ = (
        UniqueConstraint("user_id", "publisher_id", name="uq_publisher_follower"),
    )

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    user_id: Mapped[int] = mapped_column(BigInteger, nullable=False)
    publisher_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("publisher.id", ondelete="CASCADE"), nullable=False
    )
    created_at: Mapped[datetime.datetime] = mapped_column(
        DateTime, nullable=False, server_default=func.now()
    )


class BookCategory(Base):
    __tablename__ = "book_category"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    parent_id: Mapped[int | None] = mapped_column(
        BigInteger, ForeignKey("book_category.id"), nullable=True
    )
    category_name: Mapped[str] = mapped_column(Text, nullable=False)


class BookTranslation(Base):
    __tablename__ = "book_translations"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    book_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("book.id", ondelete="CASCADE"), nullable=False
    )
    lang: Mapped[str] = mapped_column(String(10), nullable=False)
    title: Mapped[str] = mapped_column(String(255), nullable=False)
    description: Mapped[str | None] = mapped_column(Text, nullable=True)
    cover_image_filename: Mapped[str | None] = mapped_column(Text, nullable=True)
    sample_url: Mapped[str | None] = mapped_column(Text, nullable=True)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    updated_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)


class BookBookCategory(Base):
    __tablename__ = "book_book_category"
    __table_args__ = (
        PrimaryKeyConstraint("book_id", "category_id", name="pk_book_book_category"),
    )

    book_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("book.id", ondelete="CASCADE"), nullable=False
    )
    category_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("book_category.id", ondelete="CASCADE"), nullable=False
    )


class Book(Base):
    __tablename__ = "book"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    author_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("author.id"), nullable=False
    )
    author: Mapped["Author"] = relationship()
    publisher_id: Mapped[int | None] = mapped_column(
        BigInteger, ForeignKey("publisher.id"), nullable=True
    )
    publisher: Mapped[Optional["Publisher"]] = relationship()
    translations: Mapped[list["BookTranslation"]] = relationship(passive_deletes=True)
    categories: Mapped[list["BookCategory"]] = relationship(
        secondary="book_book_category", passive_deletes=True
    )
    price: Mapped[float] = mapped_column(Numeric(10, 2), nullable=False)
    currency: Mapped[str] = mapped_column(String(3), nullable=False)
    language_code: Mapped[str | None] = mapped_column(String(10), nullable=True)
    isbn: Mapped[str | None] = mapped_column(String(20), nullable=True)
    product_status: Mapped[str] = mapped_column(String(20), nullable=False)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    updated_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)


class BookReview(Base):
    __tablename__ = "book_review"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    book_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("book.id", ondelete="CASCADE"), nullable=False
    )
    user_id: Mapped[int] = mapped_column(BigInteger, nullable=False)
    username: Mapped[str] = mapped_column(String(100), nullable=False)
    rating: Mapped[int] = mapped_column(SmallInteger, nullable=False)
    text: Mapped[str | None] = mapped_column(Text, nullable=True)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
