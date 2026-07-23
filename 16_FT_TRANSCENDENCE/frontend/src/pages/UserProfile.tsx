import { useEffect, useState } from 'react'
import { useParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '../hooks/useApiFetch'
import { Avatar, AvatarBadge, AvatarFallback, AvatarImage } from '../components/ui/avatar'
import { Card, CardContent } from '../components/ui/card'
import { Button } from '../components/ui/button'
import { useAuth } from '../hooks/useAuth'
import { authUrl } from '../utils/auth'

type ApiUser = {
  id: number
  username: string
  first_name?: string | null
  last_name?: string | null
  avatar_filename?: string | null
  is_online?: boolean
}

// type User = {
//   id: string
//   username: string
//   first_name?: string | null
//   last_name?: string | null
//   email: string
//   initials: string
//   avatarFilename?: string | null
// }

function getInitials(first_name?: string | null, last_name?: string | null): string {
  if (!first_name || !last_name) return ''
  if (first_name.length === 0 || last_name.length === 0) return ''
  return (first_name[0] + last_name[0]).toUpperCase()
}

// function mapUserToUser(apiUser: ApiUser): User {
//   return {
//     username: apiUser.username,
//     first_name: apiUser.first_name,
//     last_name: apiUser.last_name,
//     initials: getInitials(`${apiUser.first_name || ''} ${apiUser.last_name || ''}`),
//     avatarFilename: apiUser.avatar_filename ?? null,
//   }
// }

export default function UserProfile() {
  const { t } = useTranslation()
  const { userId } = useParams<{ userId: string }>()
  const apiFetch = useApiFetch()
  const { user: currentUser } = useAuth()
  const [user, setUser] = useState<ApiUser | null>(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)
  const [isFollowing, setIsFollowing] = useState(false)
  const [followBusy, setFollowBusy] = useState(false)
  const [followError, setFollowError] = useState<string | null>(null)

  const isOwnProfile = currentUser?.username === user?.username

  useEffect(() => {
    if (!userId) {
      return
    }

    const fetchUser = async () => {
      setLoading(true)
      setError(null)
      setFollowError(null)
      setFollowBusy(false)

      try {
        const [profileResponse, followingResponse] = await Promise.all([
          apiFetch(`/auth/users/${userId}`),
          apiFetch('/auth/me/following'),
        ])

        if (!profileResponse.ok) {
          setUser(null)
          setError(t('userProfile.unableToLoad'))
          return
        }

        const data = (await profileResponse.json()) as ApiUser
        setUser(data)

        if (followingResponse.ok) {
          const followingUsers = (await followingResponse.json()) as ApiUser[]
          setIsFollowing(
            followingUsers.some((followingUser) => String(followingUser.id) === userId)
          )
        } else {
          setIsFollowing(false)
        }
      } catch {
        setUser(null)
        setError(t('userProfile.unableToLoad'))
      } finally {
        setLoading(false)
      }
    }

    void fetchUser()
  }, [apiFetch, userId, t])

  const handleToggleFollow = async () => {
    if (!user || isOwnProfile || followBusy) {
      return
    }

    setFollowBusy(true)
    setFollowError(null)

    try {
      const url = isFollowing ? `/auth/me/unfollow/${user.id}` : `/auth/me/follow/${user.id}`
      const response = await apiFetch(url, {
        method: isFollowing ? 'DELETE' : 'POST',
      })

      if (!response.ok) {
        const errorBody = await response.json().catch(() => null)
        const detail =
          typeof errorBody?.detail === 'string' ? errorBody.detail : t('userProfile.unableToFollow')
        throw new Error(detail)
      }

      setIsFollowing((prev) => !prev)
    } catch (error) {
      setFollowError(error instanceof Error ? error.message : t('userProfile.unableToFollow'))
    } finally {
      setFollowBusy(false)
    }
  }

  if (loading) {
    return <div className="text-sm text-white/60">{t('userProfile.loading')}</div>
  }

  if (error) {
    return <div className="text-sm text-white/60">{error}</div>
  }

  if (!user) {
    return <div className="text-sm text-white/60">{t('userProfile.noData')}</div>
  }

  return (
    <Card className="border-white/10 bg-white/5 text-white">
      <CardContent className="flex items-center gap-4 p-5">
        <Avatar className="h-16 w-16">
          {user.avatar_filename ? (
            <AvatarImage src={authUrl(`/auth/users/${user.id}/avatar`)} alt={user.username} />
          ) : null}
          <AvatarFallback>
            {getInitials(user.first_name, user.last_name) ||
              user.username.slice(0, 2).toUpperCase()}
          </AvatarFallback>
          {user.is_online && <AvatarBadge className="bg-green-500" />}
        </Avatar>
        <div className="min-w-0 space-y-1">
          <h2 className="truncate text-xl font-semibold">{user.username}</h2>
          <p className="truncate text-sm text-white/60">
            {user.first_name} {user.last_name}
          </p>
        </div>
        <div className="ml-auto flex flex-col items-end gap-2">
          <Button
            variant="outline"
            size="sm"
            className="min-w-24"
            onClick={handleToggleFollow}
            disabled={followBusy || isOwnProfile}
          >
            {isOwnProfile
              ? t('userProfile.thisIsYou')
              : isFollowing
                ? t('userProfile.following')
                : followBusy
                  ? t('userProfile.followingBusy')
                  : t('userProfile.follow')}
          </Button>
          {followError && <p className="text-xs text-red-300">{followError}</p>}
        </div>
      </CardContent>
    </Card>
  )
}
