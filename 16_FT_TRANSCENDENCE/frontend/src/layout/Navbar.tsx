import { useEffect, useRef, useState, type KeyboardEvent } from 'react'
import { Link, useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import logoWhite from '../assets/logo-white.png'
import logoOrange from '../assets/logo-orange.png'
import { useAuth } from '../hooks/useAuth.ts'
import { useSidebar } from '../components/ui/sidebar.tsx'
import { UserAvatar } from '../components/ui/avatar.tsx'
import { authUrl } from '../utils/auth.ts'
import {
  searchMatchLabel,
  searchResultPath,
  searchResultTypeLabel,
  type SearchResult,
} from '../utils/search.ts'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'
const MIN_SEARCH_LENGTH = 2

export default function Navbar() {
  const { t, i18n } = useTranslation()
  const isRTL = i18n.language === 'ar'
  const { token, user } = useAuth()
  const { toggleSidebar } = useSidebar()
  const navigate = useNavigate()
  const searchRef = useRef<HTMLDivElement>(null)
  const [query, setQuery] = useState('')
  const [results, setResults] = useState<SearchResult[]>([])
  const [loading, setLoading] = useState(false)
  const [searchError, setSearchError] = useState(false)
  const [isSearchOpen, setIsSearchOpen] = useState(false)
  const [highlightedIndex, setHighlightedIndex] = useState<number | null>(null)
  const trimmedQuery = query.trim()
  const isSearchable = trimmedQuery.length >= MIN_SEARCH_LENGTH
  const visibleResults = isSearchable ? results : []
  const visibleLoading = isSearchable && loading
  const visibleSearchError = isSearchable && searchError

  useEffect(() => {
    if (!isSearchable) return

    const controller = new AbortController()
    const timeoutId = window.setTimeout(() => {
      setLoading(true)
      setSearchError(false)

      fetch(`${API_URL}/search?q=${encodeURIComponent(trimmedQuery)}&limit=6`, {
        signal: controller.signal,
        credentials: 'include',
      })
        .then((response) => {
          if (!response.ok) throw new Error(`HTTP ${response.status}`)
          return response.json()
        })
        .then((data: SearchResult[]) => {
          setResults(Array.isArray(data) ? data : [])
          setHighlightedIndex(null)
          setIsSearchOpen(true)
        })
        .catch((error) => {
          if (error.name === 'AbortError') return
          setResults([])
          setSearchError(true)
        })
        .finally(() => {
          if (!controller.signal.aborted) setLoading(false)
        })
    }, 180)

    return () => {
      window.clearTimeout(timeoutId)
      controller.abort()
    }
  }, [isSearchable, trimmedQuery])

  useEffect(() => {
    const handlePointerDown = (event: PointerEvent) => {
      if (!searchRef.current?.contains(event.target as Node)) {
        setIsSearchOpen(false)
      }
    }

    document.addEventListener('pointerdown', handlePointerDown)
    return () => document.removeEventListener('pointerdown', handlePointerDown)
  }, [])

  const openResult = (result: SearchResult) => {
    setQuery('')
    setResults([])
    setIsSearchOpen(false)
    navigate(searchResultPath(result))
  }

  const openSearchPage = () => {
    if (trimmedQuery.length < MIN_SEARCH_LENGTH) return
    setIsSearchOpen(false)
    navigate(`/search?q=${encodeURIComponent(trimmedQuery)}`)
  }

  const handleSearchKeyDown = (event: KeyboardEvent<HTMLInputElement>) => {
    if (!isSearchOpen || visibleResults.length === 0) {
      if (event.key === 'Escape') setIsSearchOpen(false)
      if (event.key === 'Enter') {
        event.preventDefault()
        openSearchPage()
      }
      return
    }

    if (event.key === 'ArrowDown') {
      event.preventDefault()
      setHighlightedIndex((current) =>
        current === null ? 0 : (current + 1) % visibleResults.length
      )
    } else if (event.key === 'ArrowUp') {
      event.preventDefault()
      setHighlightedIndex((current) =>
        current === null
          ? visibleResults.length - 1
          : (current - 1 + visibleResults.length) % visibleResults.length
      )
    } else if (event.key === 'Enter') {
      event.preventDefault()
      if (highlightedIndex === null) {
        openSearchPage()
      } else {
        openResult(visibleResults[highlightedIndex])
      }
    } else if (event.key === 'Escape') {
      setIsSearchOpen(false)
    }
  }

  const showSearchMenu = isSearchOpen && isSearchable

  return (
    <header
      dir="ltr"
      style={{
        height: '60px',
        backgroundColor: '#111',
        borderBottom: '1px solid rgba(255,255,255,0.1)',
        display: 'flex',
        alignItems: 'center',
        padding: '0 24px',
        gap: '16px',
        flexShrink: 0,
        position: 'relative',
        zIndex: 50,
      }}
    >
      {/* Logo — Home Button */}
      <Link
        to="/"
        style={{ display: 'flex', flexShrink: 0, textDecoration: 'none', userSelect: 'none' }}
      >
        <div className="group relative w-8 h-8 flex-shrink-0 cursor-pointer">
          {/* White Logo (Default) */}
          <img
            src={logoWhite}
            alt="Logo"
            draggable="false"
            className="absolute inset-0 w-full h-full object-contain transition-opacity duration-200 group-hover:opacity-0 select-none"
          />
          {/* Orange Logo (Visible on Hover) */}
          <img
            src={logoOrange}
            alt="Logo Hover"
            draggable="false"
            className="absolute inset-0 w-full h-full object-contain transition-opacity duration-200 opacity-0 group-hover:opacity-100 select-none"
          />
        </div>
      </Link>

      {/* Search */}
      <div
        ref={searchRef}
        style={{
          position: 'relative',
          flex: 1,
          maxWidth: '620px',
          minWidth: '180px',
          margin: '0 auto',
        }}
      >
        <input
          dir={isRTL ? 'rtl' : 'ltr'}
          value={query}
          onChange={(event) => {
            setQuery(event.target.value)
            setHighlightedIndex(null)
            setIsSearchOpen(true)
          }}
          onFocus={() => {
            if (trimmedQuery.length >= MIN_SEARCH_LENGTH) setIsSearchOpen(true)
          }}
          onKeyDown={handleSearchKeyDown}
          placeholder={t('nav.searchPlaceholder')}
          aria-label={t('nav.searchAriaLabel')}
          aria-expanded={showSearchMenu}
          aria-controls="navbar-search-results"
          style={{
            width: '100%',
            background: 'rgba(255,255,255,0.07)',
            border: '1px solid rgba(255,255,255,0.1)',
            borderRadius: '8px',
            padding: '8px 16px',
            color: 'white',
            fontSize: '14px',
            outline: 'none',
          }}
        />

        {showSearchMenu && (
          <div
            id="navbar-search-results"
            role="listbox"
            style={{
              position: 'absolute',
              top: 'calc(100% + 8px)',
              left: 0,
              right: 0,
              background: '#171717',
              border: '1px solid rgba(255,255,255,0.12)',
              borderRadius: '8px',
              boxShadow: '0 18px 40px rgba(0,0,0,0.45)',
              overflow: 'hidden',
              zIndex: 80,
            }}
          >
            {visibleLoading && (
              <div style={{ padding: '12px 14px', color: 'rgba(255,255,255,0.65)', fontSize: 13 }}>
                {t('nav.searching')}
              </div>
            )}

            {!visibleLoading && visibleSearchError && (
              <div style={{ padding: '12px 14px', color: 'rgba(255,255,255,0.65)', fontSize: 13 }}>
                {t('nav.searchUnavailable')}
              </div>
            )}

            {!visibleLoading && !visibleSearchError && visibleResults.length === 0 && (
              <div style={{ padding: '12px 14px', color: 'rgba(255,255,255,0.65)', fontSize: 13 }}>
                {t('nav.noMatches')}
              </div>
            )}

            {!visibleLoading &&
              !visibleSearchError &&
              visibleResults.map((result, index) => {
                const isHighlighted = index === highlightedIndex
                return (
                  <button
                    key={`${result.result_type}-${result.id}-${result.matched_field}-${result.matched_text}`}
                    type="button"
                    role="option"
                    aria-selected={isHighlighted}
                    onMouseEnter={() => setHighlightedIndex(index)}
                    onClick={() => openResult(result)}
                    style={{
                      width: '100%',
                      display: 'block',
                      textAlign: 'left',
                      border: 'none',
                      borderBottom:
                        index === visibleResults.length - 1
                          ? 'none'
                          : '1px solid rgba(255,255,255,0.07)',
                      background: isHighlighted ? 'rgba(255,255,255,0.09)' : 'transparent',
                      color: 'white',
                      cursor: 'pointer',
                      padding: '10px 14px',
                    }}
                  >
                    <div style={{ fontSize: 14, fontWeight: 600, lineHeight: 1.25 }}>
                      {result.title}
                    </div>
                    <div
                      style={{
                        marginTop: 3,
                        display: 'flex',
                        gap: 8,
                        color: 'rgba(255,255,255,0.6)',
                        fontSize: 12,
                        lineHeight: 1.3,
                      }}
                    >
                      <span>{searchResultTypeLabel(result)}</span>
                      <span aria-hidden="true">-</span>
                      <span>
                        {searchMatchLabel(result.matched_field)}: {result.matched_text}
                      </span>
                    </div>
                  </button>
                )
              })}
          </div>
        )}
      </div>

      <div style={{ display: 'flex', alignItems: 'center', gap: '12px' }}>
        {!token && (
          <Link
            to="/login"
            style={{
              textDecoration: 'none',
              color: '#f8f8f8',
              border: '1px solid rgba(255,255,255,0.25)',
              padding: '6px 12px',
              borderRadius: '999px',
              fontSize: '13px',
              letterSpacing: '0.4px',
              background: 'rgba(255,255,255,0.04)',
            }}
          >
            {t('nav.logIn')}
          </Link>
        )}
        {token && (
          <button
            type="button"
            onClick={toggleSidebar}
            aria-label={t('nav.toggleSidebar')}
            style={{
              width: '36px',
              height: '36px',
              borderRadius: '50%',
              cursor: 'pointer',
              flexShrink: 0,
              border: '1px solid rgba(255,255,255,0.2)',
              transition: 'border-color 0.2s ease',
              position: 'relative',
              zIndex: 60,
              overflow: 'hidden',
              padding: 0,
              background: 'rgba(255,255,255,0.06)',
            }}
          >
            <UserAvatar
              className="h-full w-full rounded-full text-[11px]"
              src={user?.avatar_filename ? authUrl('/auth/me/avatar') : null}
              name={user?.username}
            />
          </button>
        )}
      </div>
    </header>
  )
}
