import { useEffect, useState } from 'react'
import { useParams, Navigate } from 'react-router-dom'
import GenreHero from '../components/genre/GenreHero'
import SubgenreSection from '../components/genre/SubgenreSection'
import GenreBooksSection from '../components/genre/GenreBooksSection'
import { toSlug } from '../utils/toSlug'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

/** Frontend-only metadata: color + emoji per genre slug. */
const GENRE_META: Record<string, { color: string; icon: string }> = {
  fantasy: { color: '#a855f7', icon: '🧙' },
  'sci-fi': { color: '#0891b2', icon: '🚀' },
  'science-fiction': { color: '#3b82f6', icon: '🚀' },
  mystery: { color: '#8b5cf6', icon: '🕵️' },
  romance: { color: '#ec4899', icon: '💕' },
  horror: { color: '#dc2626', icon: '👁️' },
  biography: { color: '#10b981', icon: '📖' },
  history: { color: '#eab308', icon: '🏛️' },
  thriller: { color: '#ef4444', icon: '🔪' },
  classical: { color: '#f97316', icon: '🏛️' },
  comedy: { color: '#06b6d4', icon: '😄' },
  'self-improvement': { color: '#22c55e', icon: '🌱' },
  philosophy: { color: '#6366f1', icon: '🤔' },
}

export interface ApiCategory {
  id: number
  name: string
  parent_id: number | null
}

export default function GenrePage() {
  const { genreId } = useParams<{ genreId: string }>()
  const meta = genreId ? (GENRE_META[genreId] ?? { color: '#6b7280', icon: '📚' }) : null

  const [genre, setGenre] = useState<ApiCategory | null>(null)
  const [subgenres, setSubgenres] = useState<ApiCategory[]>([])
  const [activeSubId, setActiveSubId] = useState<number | null>(null)
  const [notFound, setNotFound] = useState(false)

  useEffect(() => {
    if (!genreId) return

    fetch(`${API_URL}/categories`)
      .then((r) => (r.ok ? r.json() : []))
      .then((cats: ApiCategory[]) => {
        const matched = cats.find((c) => c.parent_id === null && toSlug(c.name) === genreId)
        if (!matched) {
          setNotFound(true)
          return
        }
        setGenre(matched)
        setSubgenres(cats.filter((c) => c.parent_id === matched.id))
      })
      .catch(() => setNotFound(true))
  }, [genreId])

  if (notFound) return <Navigate to="/" replace />
  if (!genre || !meta) return null

  const activeCategoryId = activeSubId ?? genre.id

  /** If everything is loaded, display the content */
  return (
    <div className="flex flex-col gap-8 pb-8">
      <GenreHero
        name={genre.name}
        icon={meta.icon}
        color={meta.color}
        subgenresCount={subgenres.length}
      />
      <SubgenreSection
        subgenres={subgenres}
        activeId={activeSubId}
        color={meta.color}
        onSelect={setActiveSubId}
      />
      <GenreBooksSection categoryId={activeCategoryId} color={meta.color} />
    </div>
  )
}
