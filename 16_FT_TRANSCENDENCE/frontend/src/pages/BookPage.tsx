import { useEffect, useState } from 'react'
import { useParams, Navigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import type { Book } from '../components/book/types.ts'
import BookHero from '../components/book/BookHero.tsx'
import BookDescription from '../components/book/BookDescription.tsx'
import SimilarBooks from '../components/book/SimilarBooks.tsx'
import BookRatings from '../components/book/BookRatings.tsx'
import { toSlug } from '../utils/toSlug.ts'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

export interface ApiBook {
  id: number
  translations: { title: string; lang: string }[]
}

export interface PublicAudioFile {
  id: number
  original_filename: string
  mime_type: string
  duration_seconds: number | null
}

export default function BookPage() {
  const { bookId } = useParams<{ bookId: string }>()
  const { i18n } = useTranslation()

  const [book, setBook] = useState<Book | null>(null)
  const [audioFiles, setAudioFiles] = useState<PublicAudioFile[]>([])
  const [notFound, setNotFound] = useState(false)
  const [selectedLang, setSelectedLang] = useState<string | null>(null)

  useEffect(() => {
    if (!bookId) return

    const controller = new AbortController()

    fetch(`${API_URL}/books`, { signal: controller.signal, credentials: 'include' })
      .then((r) => (r.ok ? r.json() : []))
      .then((books: ApiBook[]) => {
        const matched = books.find((b) => b.translations.some((t) => toSlug(t.title) === bookId))
        if (!matched) {
          setNotFound(true)
          return
        }

        return Promise.all([
          fetch(`${API_URL}/books/${matched.id}`, {
            signal: controller.signal,
            credentials: 'include',
          }).then((r) => {
            if (!r.ok) throw new Error(`HTTP ${r.status}`)
            return r.json() as Promise<Book>
          }),
          fetch(`${API_URL}/audio/public/${matched.id}`, {
            signal: controller.signal,
            credentials: 'include',
          }).then((r) => (r.ok ? (r.json() as Promise<PublicAudioFile[]>) : [])),
        ]).then(([data, files]) => {
          setBook({ ...data, id: data.id ?? matched.id })
          setAudioFiles(Array.isArray(files) ? files : [])
          const uiLang = i18n.language
          const available = data.translations.map((t) => t.lang)
          const best = available.includes(uiLang) ? uiLang : (data.translations[0]?.lang ?? 'en')
          setSelectedLang(best)
        })
      })
      .catch((err) => {
        if (err.name === 'AbortError') return
        setNotFound(true)
      })

    return () => controller.abort()
  }, [bookId, i18n.language])

  if (notFound) return <Navigate to="/" replace />
  if (!book) return null

  return (
    <main className="flex-1 overflow-y-auto px-8 py-8">
      <div className="max-w-4xl mx-auto flex flex-col gap-10">
        <BookHero
          book={book}
          selectedLang={selectedLang ?? book.translations[0]?.lang ?? 'en'}
          onLangChange={setSelectedLang}
          audioFiles={audioFiles}
        />
        <BookDescription
          translations={book.translations}
          lang={selectedLang ?? book.translations[0]?.lang ?? 'en'}
        />
        <SimilarBooks bookId={String(book.id)} />
        <BookRatings bookId={book.id} />
      </div>
    </main>
  )
}
