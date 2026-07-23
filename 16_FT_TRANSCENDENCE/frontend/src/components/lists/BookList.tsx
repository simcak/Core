/**
 * BookList — centralised book-listing component.
 *
 * Supports two layout modes:
 *   - "grid"   — responsive auto-fill grid (no horizontal scroll bar)
 *   - "scroll" — single horizontal scrollable row
 *
 * Data can come from:
 *   - `books` + `loading` props  → fully controlled (parent owns the data)
 *   - `fetchUrl`                 → self-fetching (component manages its own state)
 * - ! TODO: controlled mode needs to be removed once we have backend support for the shelf page
 */

import { useEffect, useRef, useState } from 'react'
import { useTranslation } from 'react-i18next'
import { Link, useNavigate } from 'react-router-dom'
import type { ShortBook } from '../book/types.ts'
import { getTitle, getCover, getBookSlug } from '../../utils/book.ts'
import { useBookLocale } from '../../utils/useBookLocale.ts'
import { generateBookBackground } from '../../utils/randBackgroundGen.ts'
import { ScrollBtn } from './scrollButton.tsx'
import { isLoggedIn, requestLogin } from '../../utils/auth.ts'
import { useApiFetch } from '../../hooks/useApiFetch.ts'
import { handleScroll } from '../../utils/scroll.ts'

// ─── ScrollingText ────────────────────────────────────────────────────────────
// Scrolls text horizontally when it overflows, like a music player ticker.
// Pauses at start and end so the user can read comfortably.

function ScrollingText({ text, className = '' }: { text: string; className?: string }) {
  const containerRef = useRef<HTMLDivElement>(null)
  const spanRef = useRef<HTMLSpanElement>(null)

  const handleMouseEnter = () => {
    const container = containerRef.current
    const span = spanRef.current
    if (!container || !span) return
    // Only animate if the text is actually wider than its container
    if (span.scrollWidth > container.clientWidth) {
      span.style.animation = 'book-marquee 6s linear infinite'
    }
  }

  const handleMouseLeave = () => {
    const span = spanRef.current
    if (!span) return
    span.style.animation = 'none'
    span.style.transform = 'translateX(0)'
  }

  return (
    <div
      ref={containerRef}
      className={`overflow-hidden whitespace-nowrap ${className}`}
      onMouseEnter={handleMouseEnter}
      onMouseLeave={handleMouseLeave}
    >
      <span ref={spanRef} style={{ display: 'inline-block' }}>
        {text}
      </span>
    </div>
  )
}

// ─── Types ────────────────────────────────────────────────────────────────────

type Layout = 'grid' | 'scroll'

interface BookListProps {
  sectionName?: string // Heading name rendered above the books
  layout?: Layout // How will be the Book-Cards arranged? -> default=="scroll"
  imageSize?: number // for 'grid' == min width, for 'scroll' == fixed width. default==160

  // ── Data — pick ONE of the two strategies ─────────────────────────────────
  /**
   * Controlled mode: pass books from the parent.
   * Pair with `loading` so the component can show a spinner.
   */
  books?: ShortBook[]
  /** Used only in controlled mode to drive the loading state. */
  loading?: boolean

  /**
   * Self-fetching mode: provide a URL and the component fetches on mount.
   * Ignored when `books` is provided.
   */
  fetchUrl?: string

  // ── Appearance ────────────────────────────────────────────────────────────
  accentColor?: string // CSS colour used for the hover ring around covers. default=="#ffffff"
  showPrice?: boolean // Show the green price badge on each card. default==true
  showScrollButtons?: boolean // Show left/right scroll buttons (scroll layout only). Default: true
  emptyMessage?: string // Message shown only when the list is empty
  className?: string // Extra className for the outermost wrapper
}

// ─── Component ────────────────────────────────────────────────────────────────

export default function BookList({
  sectionName,
  layout = 'scroll',
  imageSize = 160,
  books: booksProp,
  loading: loadingProp,
  fetchUrl,
  accentColor = '#ffffff',
  showPrice = false,
  showScrollButtons = true,
  emptyMessage,
  className = '',
}: BookListProps) {
  const { t } = useTranslation()
  const navigate = useNavigate()
  const lang = useBookLocale()
  const scrollRef = useRef<HTMLDivElement>(null)

  // ── Internal fetch state (self-fetching mode) ──────────────────────────────
  const [fetchedBooks, setFetchedBooks] = useState<ShortBook[]>([])
  const [fetchedLoading, setFetchedLoading] = useState(false)

  const isControlled = booksProp !== undefined
  const books = isControlled ? booksProp : fetchedBooks
  const loading = isControlled ? (loadingProp ?? false) : fetchedLoading
  const apiFetch = useApiFetch()
  useEffect(() => {
    if (isControlled || !fetchUrl) return

    const controller = new AbortController()

    apiFetch(fetchUrl, { signal: controller.signal })
      .then((r) => (r.ok ? r.json() : []))
      .then((data: ShortBook[]) => {
        setFetchedBooks(Array.isArray(data) ? data : [])
        setFetchedLoading(false)
      })
      .catch(() => setFetchedLoading(false))

    return () => controller.abort()
  }, [fetchUrl, isControlled, apiFetch])

  // ── Helpers ────────────────────────────────────────────────────────────────
  const scroll = (dir: 'left' | 'right') => handleScroll(scrollRef, dir)

  // ── Card renderer (shared by both layouts) ─────────────────────────────────
  const renderCard = (book: ShortBook) => {
    const title = getTitle(book.translations, lang)
    const coverFile = getCover(book.translations, lang)
    // const background = coverFile ? `url(${coverFile})` : generateBookBackground(book.id)

    const coverStyle: React.CSSProperties = {
      width: layout === 'scroll' ? `${imageSize}px` : '100%',
      aspectRatio: '3 / 4',
      // background,
      // backgroundSize: 'cover',
      borderRadius: 8,
      marginBottom: 8,
      boxShadow: `0 0 0 0px ${accentColor}`,
      transition: 'box-shadow 0.2s, transform 0.2s',
    }

    const cardStyle: React.CSSProperties =
      layout === 'scroll'
        ? {
            flexShrink: 0,
            width: `${imageSize}px`,
          }
        : {
            width: '100%',
          }

    const cardButtonStyle: React.CSSProperties = {
      width: '100%',
      background: 'none',
      border: 'none',
      padding: 0,
      cursor: 'pointer',
      textAlign: 'left',
    }

    const openBook = () => {
      if (!isLoggedIn()) {
        requestLogin()
        return
      }
      navigate(`/book/${getBookSlug(book.translations)}`)
    }

    return (
      <div key={book.id} style={cardStyle} className="group">
        <button type="button" onClick={openBook} style={cardButtonStyle}>
          <div className="relative">
            {coverFile ? (
              <img
                loading="lazy"
                style={coverStyle}
                src={`/covers/${coverFile}`}
                alt="Book cover"
                className="w-full h-full object-cover"
                onMouseEnter={(e) => {
                  const el = e.currentTarget as HTMLElement
                  el.style.boxShadow = `0 0 0 2px ${accentColor}88`
                  el.style.transform = 'scale(1.02)'
                }}
                onMouseLeave={(e) => {
                  const el = e.currentTarget as HTMLElement
                  el.style.boxShadow = `0 0 0 0px ${accentColor}`
                  el.style.transform = 'scale(1)'
                }}
              />
            ) : (
              <div style={{ ...coverStyle, background: generateBookBackground(book.id) }} />
            )}
            {showPrice && (
              <span className="absolute bottom-2 right-2 bg-green-700 text-white text-xs font-bold rounded-full px-2 py-0.5 shadow">
                {book.price} {book.currency}
              </span>
            )}
          </div>

          <ScrollingText
            text={title}
            className="text-white text-xs font-medium leading-tight group-hover:text-neutral-200 transition-colors"
          />
        </button>
        <Link
          to={`/author/${book.author.id}`}
          className="block text-neutral-500 hover:text-orange-400 hover:underline transition-colors"
        >
          <ScrollingText text={book.author.author_name} className="text-xs mt-0.5" />
        </Link>
      </div>
    )
  }

  // ── Render ─────────────────────────────────────────────────────────────────
  return (
    <div className={`flex flex-col gap-4 ${className}`}>
      {/* Header row */}
      {(sectionName || (layout === 'scroll' && showScrollButtons)) && (
        <div className="flex items-center justify-between">
          {sectionName && (
            <h2 className="text-xl font-semibold text-white">
              {sectionName}
              {!loading && layout === 'grid' && (
                <span
                  style={{
                    fontSize: 13,
                    fontWeight: 400,
                    color: 'rgba(255,255,255,0.35)',
                    marginLeft: 10,
                  }}
                >
                  {books.length} title{books.length !== 1 ? 's' : ''}
                </span>
              )}
            </h2>
          )}
          {layout === 'scroll' && showScrollButtons && (
            <div className="flex gap-2" dir="ltr">
              <ScrollBtn dir="left" onClick={() => scroll('left')} />
              <ScrollBtn dir="right" onClick={() => scroll('right')} />
            </div>
          )}
        </div>
      )}

      {/* Loading state */}
      {loading && (
        <p className="text-sm" style={{ color: 'rgba(255,255,255,0.3)' }}>
          {t('book.loading')}
        </p>
      )}

      {/* Empty state */}
      {!loading && books.length === 0 && (
        <p className="text-sm" style={{ color: 'rgba(255,255,255,0.3)', fontStyle: 'italic' }}>
          {emptyMessage ?? t('book.noBooksFound')}
        </p>
      )}

      {/* Book cards */}
      {!loading &&
        books.length > 0 &&
        (layout === 'grid' ? (
          <div
            style={{
              display: 'grid',
              gridTemplateColumns: `repeat(auto-fill, minmax(${imageSize}px, 1fr))`,
              gap: '1rem',
            }}
          >
            {books.map(renderCard)}
          </div>
        ) : (
          <div
            ref={scrollRef}
            className="flex gap-4 overflow-x-auto p-2"
            style={{ scrollbarWidth: 'none' }}
          >
            {books.map(renderCard)}
          </div>
        ))}
    </div>
  )
}
