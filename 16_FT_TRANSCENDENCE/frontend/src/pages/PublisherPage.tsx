import { useEffect, useState } from 'react'
import { useParams, Navigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '../hooks/useApiFetch'
import { useAuth } from '../hooks/useAuth'
import { Avatar, AvatarFallback } from '../components/ui/avatar'
import { Card, CardContent } from '../components/ui/card'
import { Button } from '../components/ui/button'
import BookList from '../components/lists/BookList'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface ApiPublisher {
  id: number
  publisher_name: string
}

function getInitials(name: string) {
  const parts = name.trim().split(/\s+/).filter(Boolean)
  if (parts.length === 0) return ''
  if (parts.length === 1) return parts[0].slice(0, 2).toUpperCase()
  return (parts[0][0] + parts[parts.length - 1][0]).toUpperCase()
}

export default function PublisherPage() {
  const { t } = useTranslation()
  const { publisherId } = useParams<{ publisherId: string }>()
  const apiFetch = useApiFetch()
  const { user } = useAuth()
  const [publisher, setPublisher] = useState<ApiPublisher | null>(null)
  const [loading, setLoading] = useState(true)
  const [notFound, setNotFound] = useState(false)
  const [isFollowing, setIsFollowing] = useState(false)
  const [followBusy, setFollowBusy] = useState(false)
  const [followError, setFollowError] = useState<string | null>(null)

  useEffect(() => {
    if (!publisherId) return

    const controller = new AbortController()

    const fetchPublisher = async () => {
      setLoading(true)
      setNotFound(false)
      setFollowError(null)

      try {
        const followingPromise: Promise<Response | null> = user
          ? apiFetch(`${API_URL}/me/following/publishers`, { signal: controller.signal })
          : Promise.resolve(null)

        const [response, followingResponse] = await Promise.all([
          apiFetch(`${API_URL}/publishers/${publisherId}`, { signal: controller.signal }),
          followingPromise,
        ])

        if (!response.ok) throw new Error(`HTTP ${response.status}`)
        setPublisher((await response.json()) as ApiPublisher)

        if (followingResponse?.ok) {
          const followedPublishers = (await followingResponse.json()) as ApiPublisher[]
          setIsFollowing(followedPublishers.some((followed) => String(followed.id) === publisherId))
        } else {
          setIsFollowing(false)
        }
      } catch (err) {
        if (err instanceof Error && err.name === 'AbortError') return
        setNotFound(true)
      } finally {
        setLoading(false)
      }
    }

    void fetchPublisher()

    return () => controller.abort()
  }, [publisherId, apiFetch, user])

  const handleToggleFollow = async () => {
    if (!publisher || followBusy) return

    if (!user) {
      setFollowError(t('publisher.loginToFollow'))
      return
    }

    setFollowBusy(true)
    setFollowError(null)

    try {
      const response = await apiFetch(`${API_URL}/publishers/${publisher.id}/follow`, {
        method: isFollowing ? 'DELETE' : 'POST',
      })

      if (!response.ok) {
        const errorBody = await response.json().catch(() => null)
        const detail =
          typeof errorBody?.detail === 'string' ? errorBody.detail : t('publisher.unableToFollow')
        throw new Error(detail)
      }

      setIsFollowing((prev) => !prev)
    } catch (err) {
      setFollowError(err instanceof Error ? err.message : t('publisher.unableToFollow'))
    } finally {
      setFollowBusy(false)
    }
  }

  if (notFound) return <Navigate to="/" replace />

  if (loading || !publisher) {
    return <div className="text-sm text-white/60">{t('publisher.loading')}</div>
  }

  return (
    <div className="flex flex-col gap-8 pb-8">
      <Card className="border-white/10 bg-white/5 text-white">
        <CardContent className="flex items-center gap-4 p-5">
          <Avatar className="h-16 w-16">
            <AvatarFallback>{getInitials(publisher.publisher_name)}</AvatarFallback>
          </Avatar>
          <div className="min-w-0 space-y-1">
            <h2 className="truncate text-xl font-semibold">{publisher.publisher_name}</h2>
            <p className="truncate text-sm text-white/60">{t('publisher.roleLabel')}</p>
          </div>
          <div className="ml-auto flex flex-col items-end gap-2">
            <Button
              variant="outline"
              size="sm"
              className="min-w-24"
              onClick={handleToggleFollow}
              disabled={followBusy}
            >
              {isFollowing
                ? t('publisher.following')
                : followBusy
                  ? t('publisher.saving')
                  : t('publisher.follow')}
            </Button>
            {followError && <p className="text-xs text-red-300">{followError}</p>}
          </div>
        </CardContent>
      </Card>

      <BookList
        sectionName={t('publisher.books')}
        fetchUrl={`${API_URL}/books?publisher_id=${publisher.id}&status=active`}
        layout="grid"
        imageSize={160}
        emptyMessage={t('publisher.noBooks')}
      />
    </div>
  )
}
