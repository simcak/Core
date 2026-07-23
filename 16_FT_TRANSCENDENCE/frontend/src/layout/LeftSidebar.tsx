// TODO: redesing for logged in users (show bought book list, etc.)

import { useEffect, useState } from 'react'
import { NavLink, useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import type { ShortBook } from '../components/book/types.ts'
import { getCover, getTitle, getBookSlug } from '../utils/book.ts'
import { useBookLocale } from '../utils/useBookLocale.ts'
import { isLoggedIn, requestLogin } from '../utils/auth.ts'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

export default function LeftSidebar() {
  const { t, i18n } = useTranslation()
  const navigate = useNavigate()
  const lang = useBookLocale()
  const isRTL = i18n.language === 'ar'
  const [books, setBooks] = useState<ShortBook[]>([])

  useEffect(() => {
    const controller = new AbortController()
    fetch(`${API_URL}/books?status=active`, { signal: controller.signal })
      .then((r) => (r.ok ? r.json() : []))
      .then((data: ShortBook[]) => setBooks(data))
      .catch(() => {})
    return () => controller.abort()
  }, [])
  const bookCover = (book: ShortBook) => {
    return getCover(book.translations, lang)
  }
  return (
    <aside
      dir={isRTL ? 'rtl' : 'ltr'}
      style={{
        width: 'var(--left-sidebar-width)',
        borderRight: '1px solid rgba(255,255,255,0.1)',
        padding: '20px 16px',
        flexShrink: 0,
        overflowY: 'auto',
        display: 'flex',
        flexDirection: 'column',
        gap: 12,
      }}
    >
      {/* Header link → /shelf */}
      <NavLink
        to="/shelf"
        onClick={(event) => {
          if (!isLoggedIn()) {
            event.preventDefault()
            requestLogin()
          }
        }}
        style={{
          fontSize: '22px',
          textDecoration: 'none',
          transition: 'color 0.2s',
          fontWeight: 400,
          flexShrink: 0,
        }}
        onMouseEnter={(e) => {
          ;(e.currentTarget as HTMLElement).style.color = 'rgba(237,106,55,1)'
        }}
        onMouseLeave={(e) => {
          ;(e.currentTarget as HTMLElement).style.color = 'rgba(255,255,255,0.9)'
        }}
      >
        {t('leftSidebar.bookShelf')}
      </NavLink>

      {/* Book list */}
      {books.length === 0 ? (
        <p style={{ fontSize: 13, color: 'rgba(255,255,255,0.25)', fontStyle: 'italic' }}>
          {t('leftSidebar.loginForShelf')}
        </p>
      ) : (
        <div style={{ display: 'flex', flexDirection: 'column', gap: 8 }}>
          {books.map((book) => {
            const title = getTitle(book.translations, lang)
            const openBook = () => {
              if (!isLoggedIn()) {
                requestLogin()
                return
              }
              navigate(`/book/${getBookSlug(book.translations)}`)
            }
            return (
              <div
                key={book.id}
                style={{
                  display: 'flex',
                  alignItems: 'center',
                  gap: 10,
                  padding: '4px 0',
                  width: '100%',
                }}
              >
                {/* Small cover */}
                <button
                  type="button"
                  onClick={openBook}
                  aria-label={`${t('leftSidebar.bookCover')} – ${title}`}
                  style={{
                    width: 36,
                    height: 48,
                    flexShrink: 0,
                    borderRadius: 6,
                    backgroundSize: 'cover',
                    border: 'none',
                    cursor: 'pointer',
                    padding: 0,
                  }}
                >
                  <img
                    src={`/covers/${bookCover(book)}`}
                    alt={t('leftSidebar.bookCover')}
                    className="w-full h-full object-cover"
                  />
                </button>

                {/* Title + author */}
                <div style={{ overflow: 'hidden' }}>
                  <button
                    type="button"
                    onClick={openBook}
                    style={{
                      fontSize: 12,
                      fontWeight: 600,
                      color: 'rgba(255,255,255,0.85)',
                      lineHeight: 1.3,
                      whiteSpace: 'nowrap',
                      overflow: 'hidden',
                      textOverflow: 'ellipsis',
                      background: 'transparent',
                      border: 'none',
                      cursor: 'pointer',
                      display: 'block',
                      padding: 0,
                      textAlign: 'start',
                      width: '100%',
                    }}
                    onMouseEnter={(e) => {
                      ;(e.currentTarget as HTMLElement).style.color = 'rgba(237,106,55,1)'
                    }}
                    onMouseLeave={(e) => {
                      ;(e.currentTarget as HTMLElement).style.color = 'rgba(255,255,255,0.9)'
                    }}
                  >
                    {title}
                  </button>
                  <NavLink
                    to={`/author/${book.author.id}`}
                    style={{
                      display: 'block',
                      fontSize: 11,
                      color: 'rgba(255,255,255,0.35)',
                      whiteSpace: 'nowrap',
                      overflow: 'hidden',
                      textOverflow: 'ellipsis',
                      textDecoration: 'none',
                    }}
                    onMouseEnter={(e) => {
                      ;(e.currentTarget as HTMLElement).style.color = 'rgba(237,106,55,1)'
                    }}
                    onMouseLeave={(e) => {
                      ;(e.currentTarget as HTMLElement).style.color = 'rgba(255,255,255,0.35)'
                    }}
                  >
                    {book.author.author_name}
                  </NavLink>
                </div>
              </div>
            )
          })}
        </div>
      )}
    </aside>
  )
}
