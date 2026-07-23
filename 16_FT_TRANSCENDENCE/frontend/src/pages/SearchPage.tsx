import { useEffect, useState } from 'react'
import { Link, useSearchParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { Avatar, AvatarFallback, AvatarImage } from '../components/ui/avatar'
import { authUrl } from '../utils/auth'
import {
  searchMatchLabel,
  searchResultPath,
  searchResultTypeLabel,
  type SearchResult,
} from '../utils/search'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'
const MIN_SEARCH_LENGTH = 2
const SEARCH_PAGE_SIZE = 8
const SEARCH_FILTERS = ['all', 'users', 'books', 'authors', 'publishers'] as const

type SearchFilter = (typeof SEARCH_FILTERS)[number]

interface UserSearchResult {
  id: number
  username: string
  first_name: string | null
  last_name: string | null
  avatar_filename: string | null
}

function resultTypeTitle(result: SearchResult) {
  if (result.result_type === 'author') return 'Author'
  if (result.result_type === 'publisher') return 'Publisher'
  if (result.result_type === 'genre') return 'Genre'
  return 'Book'
}

function getInitials(value: string) {
  const parts = value.trim().split(/\s+/).filter(Boolean)
  if (parts.length === 0) return ''
  if (parts.length === 1) return parts[0].slice(0, 2).toUpperCase()
  return (parts[0][0] + parts[parts.length - 1][0]).toUpperCase()
}

function userDisplayName(user: UserSearchResult) {
  return [user.first_name, user.last_name].filter(Boolean).join(' ')
}

function parseSearchFilter(value: string | null): SearchFilter {
  return SEARCH_FILTERS.includes(value as SearchFilter) ? (value as SearchFilter) : 'all'
}

export default function SearchPage() {
  const { t } = useTranslation()
  const [searchParams, setSearchParams] = useSearchParams()
  const query = searchParams.get('q')?.trim() ?? ''
  const activeFilter = parseSearchFilter(searchParams.get('type'))
  const shouldSearchUsers = activeFilter === 'all' || activeFilter === 'users'
  const shouldSearchCatalog = activeFilter !== 'users'
  const [results, setResults] = useState<SearchResult[]>([])
  const [userResults, setUserResults] = useState<UserSearchResult[]>([])
  const [loading, setLoading] = useState(false)
  const [catalogError, setCatalogError] = useState(false)
  const [userError, setUserError] = useState(false)
  const isSearchable = query.length >= MIN_SEARCH_LENGTH
  const visibleResults = isSearchable && shouldSearchCatalog ? results : []
  const visibleUserResults = isSearchable && shouldSearchUsers ? userResults : []
  const visibleLoading = isSearchable && loading
  const visibleCatalogError = isSearchable && shouldSearchCatalog && catalogError
  const visibleUserError = isSearchable && shouldSearchUsers && userError

  useEffect(() => {
    if (!isSearchable) return

    const controller = new AbortController()
    const timeoutId = window.setTimeout(() => {
      setLoading(true)
      setCatalogError(false)
      setUserError(false)

      const fetchCatalogResults = shouldSearchCatalog
        ? fetch(
            `${API_URL}/search?${new URLSearchParams({
              q: query,
              limit: '50',
              ...(activeFilter === 'books' ? { type: 'book' } : {}),
              ...(activeFilter === 'authors' ? { type: 'author' } : {}),
              ...(activeFilter === 'publishers' ? { type: 'publisher' } : {}),
            })}`,
            {
              signal: controller.signal,
              credentials: 'include',
            }
          ).then((response) => {
            if (!response.ok) throw new Error(`HTTP ${response.status}`)
            return response.json() as Promise<SearchResult[]>
          })
        : Promise.resolve([])

      const fetchUserResults = shouldSearchUsers
        ? fetch(authUrl(`/auth/search/users?q=${encodeURIComponent(query)}&limit=30`), {
            signal: controller.signal,
            credentials: 'include',
          }).then((response) => {
            if (!response.ok) throw new Error(`HTTP ${response.status}`)
            return response.json() as Promise<UserSearchResult[]>
          })
        : Promise.resolve([])

      Promise.allSettled([fetchCatalogResults, fetchUserResults])
        .then(([catalog, users]) => {
          if (controller.signal.aborted) return

          if (catalog.status === 'fulfilled') {
            setResults(Array.isArray(catalog.value) ? catalog.value : [])
          } else {
            setResults([])
            setCatalogError(true)
          }

          if (users.status === 'fulfilled') {
            setUserResults(Array.isArray(users.value) ? users.value : [])
          } else {
            setUserResults([])
            setUserError(true)
          }
        })
        .finally(() => {
          if (!controller.signal.aborted) setLoading(false)
        })
    }, 0)

    return () => {
      window.clearTimeout(timeoutId)
      controller.abort()
    }
  }, [activeFilter, isSearchable, query, shouldSearchCatalog, shouldSearchUsers])

  const entityResults = visibleResults.filter((result) => result.result_type !== 'book')
  const bookResults = visibleResults.filter((result) => result.result_type === 'book')
  const allItems = [
    ...visibleUserResults.map((user) => ({ kind: 'user' as const, user })),
    ...entityResults.map((result) => ({ kind: 'catalog' as const, result })),
    ...bookResults.map((result) => ({ kind: 'catalog' as const, result })),
  ]
  const requestedPage = Number(searchParams.get('page') ?? '1')
  const totalPages = Math.max(1, Math.ceil(allItems.length / SEARCH_PAGE_SIZE))
  const currentPage =
    Number.isInteger(requestedPage) && requestedPage > 0 ? Math.min(requestedPage, totalPages) : 1
  const pageStart = (currentPage - 1) * SEARCH_PAGE_SIZE
  const pageItems = allItems.slice(pageStart, pageStart + SEARCH_PAGE_SIZE)
  const pageUserResults = pageItems.flatMap((item) => (item.kind === 'user' ? [item.user] : []))
  const pageCatalogResults = pageItems.flatMap((item) =>
    item.kind === 'catalog' ? [item.result] : []
  )
  const pageEntityResults = pageCatalogResults.filter((result) => result.result_type !== 'book')
  const pageBookResults = pageCatalogResults.filter((result) => result.result_type === 'book')
  const entitySectionTitle =
    activeFilter === 'authors'
      ? t('search.authors')
      : activeFilter === 'publishers'
        ? t('search.publishers')
        : t('search.topMatch')
  const hasNoResults =
    isSearchable &&
    visibleResults.length === 0 &&
    visibleUserResults.length === 0 &&
    !visibleCatalogError &&
    !visibleUserError
  const goToPage = (page: number) => {
    const nextParams = new URLSearchParams(searchParams)
    nextParams.set('q', query)
    if (page <= 1) {
      nextParams.delete('page')
    } else {
      nextParams.set('page', String(page))
    }
    setSearchParams(nextParams)
  }
  const changeFilter = (filter: SearchFilter) => {
    const nextParams = new URLSearchParams(searchParams)
    if (query) nextParams.set('q', query)
    if (filter === 'all') {
      nextParams.delete('type')
    } else {
      nextParams.set('type', filter)
    }
    nextParams.delete('page')
    setSearchParams(nextParams)
  }

  return (
    <div className="mx-auto flex max-w-5xl flex-col gap-8 pb-8">
      <div>
        <h1 className="text-2xl font-semibold text-white">{t('search.title')}</h1>
        <p className="mt-1 text-sm text-white/50">
          {query ? t('search.results', { query }) : t('search.hint')}
        </p>
      </div>

      <div
        className="inline-flex w-full max-w-full flex-wrap gap-1 rounded-lg border border-white/10 bg-white/[0.04] p-1 sm:w-fit"
        role="tablist"
        aria-label={t('search.filterLabel')}
      >
        {SEARCH_FILTERS.map((filter) => (
          <button
            key={filter}
            type="button"
            role="tab"
            aria-selected={activeFilter === filter}
            onClick={() => changeFilter(filter)}
            className={`rounded-md px-3 py-1.5 text-sm font-medium transition-colors ${
              activeFilter === filter
                ? 'bg-orange-400/20 text-orange-100'
                : 'text-white/60 hover:bg-white/10 hover:text-white'
            }`}
          >
            {t(`search.filters.${filter}`)}
          </button>
        ))}
      </div>

      {!isSearchable && (
        <p className="text-sm text-white/50">
          {t('search.minChars', { count: MIN_SEARCH_LENGTH })}
        </p>
      )}

      {visibleLoading && <p className="text-sm text-white/50">{t('search.searching')}</p>}

      {!visibleLoading && visibleCatalogError && visibleUserError && (
        <p className="text-sm text-red-300">{t('search.unavailable')}</p>
      )}

      {!visibleLoading && hasNoResults && (
        <p className="text-sm text-white/50">{t('search.noMatches')}</p>
      )}

      {!visibleLoading && pageUserResults.length > 0 && (
        <section className="flex flex-col gap-3">
          <h2 className="text-lg font-semibold text-white">{t('search.people')}</h2>
          <div className="grid gap-3 sm:grid-cols-2">
            {pageUserResults.map((user) => {
              const displayName = userDisplayName(user)
              return (
                <Link
                  key={user.id}
                  to={`/users/${user.id}`}
                  className="flex items-center gap-3 rounded-lg border border-white/10 bg-white/[0.05] p-4 text-white transition-colors hover:border-orange-400/60 hover:bg-white/[0.08]"
                >
                  <Avatar className="h-11 w-11">
                    {user.avatar_filename ? (
                      <AvatarImage
                        src={authUrl(`/auth/users/${user.id}/avatar`)}
                        alt={user.username}
                      />
                    ) : null}
                    <AvatarFallback>{getInitials(displayName || user.username)}</AvatarFallback>
                  </Avatar>
                  <div className="min-w-0">
                    <div className="truncate font-semibold">{user.username}</div>
                    {displayName && (
                      <div className="truncate text-sm text-white/55">{displayName}</div>
                    )}
                  </div>
                </Link>
              )
            })}
          </div>
        </section>
      )}

      {!visibleLoading && visibleUserError && !visibleCatalogError && (
        <p className="text-sm text-red-300">{t('search.peopleUnavailable')}</p>
      )}

      {!visibleLoading && !visibleCatalogError && pageEntityResults.length > 0 && (
        <section className="flex flex-col gap-3">
          <h2 className="text-lg font-semibold text-white">{entitySectionTitle}</h2>
          <div className="grid gap-3 sm:grid-cols-2">
            {pageEntityResults.map((result) => (
              <Link
                key={`${result.result_type}-${result.id}`}
                to={searchResultPath(result)}
                className="rounded-lg border border-white/10 bg-white/[0.05] p-4 text-white transition-colors hover:border-orange-400/60 hover:bg-white/[0.08]"
              >
                <div className="text-xs uppercase tracking-wide text-white/40">
                  {resultTypeTitle(result)}
                </div>
                <div className="mt-1 text-lg font-semibold">{result.title}</div>
                <div className="mt-2 text-sm text-white/55">
                  {searchMatchLabel(result.matched_field)}: {result.matched_text}
                </div>
              </Link>
            ))}
          </div>
        </section>
      )}

      {!visibleLoading && !visibleCatalogError && pageBookResults.length > 0 && (
        <section className="flex flex-col gap-3">
          <h2 className="text-lg font-semibold text-white">{t('search.books')}</h2>
          <div className="overflow-hidden rounded-lg border border-white/10">
            {pageBookResults.map((result, index) => (
              <Link
                key={`book-${result.id}-${result.matched_field}-${result.matched_text}`}
                to={searchResultPath(result)}
                className="block border-white/10 bg-white/[0.03] p-4 text-white transition-colors hover:bg-white/[0.07]"
                style={{ borderTopWidth: index === 0 ? 0 : 1 }}
              >
                <div className="flex flex-wrap items-baseline justify-between gap-2">
                  <h3 className="text-base font-semibold">{result.title}</h3>
                  <span className="text-xs text-white/40">{searchResultTypeLabel(result)}</span>
                </div>
                <p className="mt-1 text-sm text-white/55">
                  {searchMatchLabel(result.matched_field)}: {result.matched_text}
                </p>
              </Link>
            ))}
          </div>
        </section>
      )}

      {!visibleLoading && visibleCatalogError && !visibleUserError && (
        <p className="text-sm text-red-300">{t('search.catalogUnavailable')}</p>
      )}

      {!visibleLoading && allItems.length > SEARCH_PAGE_SIZE && (
        <div className="flex flex-wrap items-center justify-between gap-3 border-t border-white/10 pt-4">
          <p className="text-sm text-white/45">
            {t('search.showing', {
              start: pageStart + 1,
              end: Math.min(pageStart + SEARCH_PAGE_SIZE, allItems.length),
              total: allItems.length,
            })}
          </p>
          <div className="flex items-center gap-2">
            <button
              type="button"
              disabled={currentPage === 1}
              onClick={() => goToPage(currentPage - 1)}
              className="rounded-md border border-white/10 px-3 py-1.5 text-sm text-white/80 transition-colors hover:bg-white/10 disabled:cursor-not-allowed disabled:opacity-40"
            >
              {t('search.previous')}
            </button>
            {Array.from({ length: totalPages }, (_, index) => index + 1).map((page) => (
              <button
                key={page}
                type="button"
                onClick={() => goToPage(page)}
                className={`rounded-md border px-3 py-1.5 text-sm transition-colors ${
                  page === currentPage
                    ? 'border-orange-400/70 bg-orange-400/15 text-orange-200'
                    : 'border-white/10 text-white/80 hover:bg-white/10'
                }`}
              >
                {page}
              </button>
            ))}
            <button
              type="button"
              disabled={currentPage === totalPages}
              onClick={() => goToPage(currentPage + 1)}
              className="rounded-md border border-white/10 px-3 py-1.5 text-sm text-white/80 transition-colors hover:bg-white/10 disabled:cursor-not-allowed disabled:opacity-40"
            >
              {t('search.next')}
            </button>
          </div>
        </div>
      )}
    </div>
  )
}
