import { Link } from 'react-router-dom'
import { useRef } from 'react'
import { useTranslation } from 'react-i18next'
import { ScrollBtn } from '../lists/scrollButton.tsx'
import { handleScroll } from '../../utils/scroll.ts'

const GENRES = [
  { slug: 'Classical', color: '#f97316' },
  { slug: 'Self-improvement', color: '#22c55e' },
  { slug: 'Comedy', color: '#06b6d4' },
  { slug: 'Thriller', color: '#ef4444' },
  { slug: 'Fantasy', color: '#a855f7' },
  { slug: 'Romance', color: '#ec4899' },
  { slug: 'Sci-Fi', color: '#3b82f6' },
  { slug: 'History', color: '#eab308' },
  { slug: 'Biography', color: '#10b981' },
  { slug: 'Mystery', color: '#8b5cf6' },
  { slug: 'Horror', color: '#dc2626' },
  { slug: 'Philosophy', color: '#6366f1' },
]

// Slug is derived by: name.toLowerCase().replace(/\s+/g, '-').replace(/[^a-z0-9-]/g, '')
// "Sci-Fi" → "science-fiction", "Self-improvement" → "self-improvement"
// This must match what the DB category names produce when slugified.
/** Converts a display name to a URL slug. Must match toSlug() in GenrePage. */
const toSlug = (name: string) =>
  name
    .toLowerCase()
    .replace(/\s+/g, '-')
    .replace(/[^a-z0-9-]/g, '')

export default function GenresSection() {
  const { t } = useTranslation()
  const scrollRef = useRef<HTMLDivElement>(null)
  const scroll = (dir: 'left' | 'right') => handleScroll(scrollRef, dir)

  return (
    <section style={{ marginBottom: '40px' }}>
      <div
        style={{
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'space-between',
          marginBottom: '16px',
        }}
      >
        <h2 style={{ fontSize: '20px', fontWeight: 600 }}>{t('home.genres')}</h2>
        <div style={{ display: 'flex', gap: '8px' }}>
          <ScrollBtn dir="left" onClick={() => scroll('left')} />
          <ScrollBtn dir="right" onClick={() => scroll('right')} />
        </div>
      </div>

      <div
        ref={scrollRef}
        style={{
          display: 'flex',
          gap: '16px',
          overflowX: 'auto',
          padding: '8px',
          scrollbarWidth: 'none',
        }}
      >
        {GENRES.map((genre) => (
          <Link
            key={genre.slug}
            to={`/genre/${toSlug(genre.slug)}`}
            className="px-8 py-5 rounded-2xl border
                       text-base font-bold transition-all duration-200
                       hover:scale-[1.04] active:scale-[0.97]
                       whitespace-nowrap"
            style={{
              color: genre.color,
              borderColor: `${genre.color}55`,
              boxShadow: `0 0 16px ${genre.color}18`,
              backgroundColor: 'transparent',
              textDecoration: 'none',
            }}
            onMouseEnter={(e) => (e.currentTarget.style.backgroundColor = `${genre.color}18`)}
            onMouseLeave={(e) => (e.currentTarget.style.backgroundColor = 'transparent')}
          >
            {t(`genre.names.${genre.slug}`)}
          </Link>
        ))}
      </div>
    </section>
  )
}
