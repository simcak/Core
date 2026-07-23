import { useEffect, useState } from 'react'
import { Navigate, useParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { Avatar, AvatarFallback } from '../components/ui/avatar'
import { Card, CardContent } from '../components/ui/card'
import BookList from '../components/lists/BookList'
import { useApiFetch } from '../hooks/useApiFetch'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface ApiAuthor {
  id: number
  author_name: string
}

function getInitials(name: string) {
  const parts = name.trim().split(/\s+/).filter(Boolean)
  if (parts.length === 0) return ''
  if (parts.length === 1) return parts[0].slice(0, 2).toUpperCase()
  return (parts[0][0] + parts[parts.length - 1][0]).toUpperCase()
}

export default function AuthorPage() {
  const { t } = useTranslation()
  const { authorId } = useParams<{ authorId: string }>()
  const apiFetch = useApiFetch()
  const [author, setAuthor] = useState<ApiAuthor | null>(null)
  const [loading, setLoading] = useState(true)
  const [notFound, setNotFound] = useState(false)

  useEffect(() => {
    if (!authorId) return

    const controller = new AbortController()

    const fetchAuthor = async () => {
      setLoading(true)
      setNotFound(false)

      try {
        const response = await apiFetch(`${API_URL}/authors/${authorId}`, {
          signal: controller.signal,
        })

        if (!response.ok) throw new Error(`HTTP ${response.status}`)
        setAuthor((await response.json()) as ApiAuthor)
      } catch (err) {
        if (err instanceof Error && err.name === 'AbortError') return
        setNotFound(true)
      } finally {
        setLoading(false)
      }
    }

    void fetchAuthor()

    return () => controller.abort()
  }, [authorId, apiFetch])

  if (notFound) return <Navigate to="/" replace />

  if (loading || !author) {
    return <div className="text-sm text-white/60">{t('author.loading')}</div>
  }

  return (
    <div className="flex flex-col gap-8 pb-8">
      <Card className="border-white/10 bg-white/5 text-white">
        <CardContent className="flex items-center gap-4 p-5">
          <Avatar className="h-16 w-16">
            <AvatarFallback>{getInitials(author.author_name)}</AvatarFallback>
          </Avatar>
          <div className="min-w-0 space-y-1">
            <h2 className="truncate text-xl font-semibold">{author.author_name}</h2>
            <p className="truncate text-sm text-white/60">{t('author.roleLabel')}</p>
          </div>
        </CardContent>
      </Card>

      <BookList
        sectionName={t('author.books')}
        fetchUrl={`${API_URL}/books?author_id=${author.id}&status=active`}
        layout="grid"
        imageSize={160}
        emptyMessage={t('author.noBooks')}
      />
    </div>
  )
}
