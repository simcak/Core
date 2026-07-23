import { useCallback, useEffect, useMemo, useState } from 'react'
import { useTranslation } from 'react-i18next'
import { AUTH_CHANGED_EVENT, authUrl } from '../../utils/auth'
import { useApiFetch } from '../../hooks/useApiFetch'
import { Avatar, AvatarBadge, AvatarFallback, AvatarImage, getInitials } from '../ui/avatar'
import { Button } from '../ui/button'
import { Card, CardContent } from '../ui/card'
import { Dialog, DialogContent, DialogHeader, DialogTitle } from '../ui/dialog'
import { Link } from 'react-router-dom'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

type ApiFollower = {
  id: number
  username: string
  email: string
  first_name?: string | null
  last_name?: string | null
  avatar_filename?: string | null
  is_online?: boolean
}

type ApiPublisher = {
  id: number
  publisher_name: string
}

type FollowItem = {
  id: string
  displayName: string
  subtitle: string
  initials: string
  linkTo: string
  avatarFilename: string | null
  isOnline: boolean
}

type RelationshipGroupKey = 'followers' | 'following' | 'publishers'

type RelationshipGroup = {
  key: RelationshipGroupKey
  endpoint: string
  unitLabel: string
  emptyMessageKey: string
  mapper: (data: unknown) => FollowItem[]
}

type GroupState = {
  items: FollowItem[]
  error: string | null
}

function getDisplayName(follower: ApiFollower) {
  return [follower.first_name, follower.last_name].filter(Boolean).join(' ') || follower.username
}

function mapApiUsers(data: ApiFollower[]): FollowItem[] {
  return data.map((user) => {
    const displayName = getDisplayName(user)
    return {
      id: String(user.id),
      displayName,
      subtitle: `@${user.username}`,
      initials: getInitials(displayName),
      linkTo: `/users/${user.id}`,
      avatarFilename: user.avatar_filename ?? null,
      isOnline: user.is_online ?? false,
    }
  })
}

function mapApiPublishers(data: ApiPublisher[]): FollowItem[] {
  return data.map((publisher) => ({
    id: String(publisher.id),
    displayName: publisher.publisher_name,
    subtitle: 'Publisher',
    initials: getInitials(publisher.publisher_name),
    linkTo: `/publisher/${publisher.id}`,
    avatarFilename: null,
    isOnline: false,
  }))
}

const GROUPS: RelationshipGroup[] = [
  {
    key: 'followers',
    endpoint: '/auth/me/followers',
    emptyMessageKey: 'noFollowers',
    unitLabel: 'user',
    mapper: (data) => mapApiUsers(data as ApiFollower[]),
  },
  {
    key: 'following',
    endpoint: '/auth/me/following',
    emptyMessageKey: 'followingSoon',
    unitLabel: 'user',
    mapper: (data) => mapApiUsers(data as ApiFollower[]),
  },
  {
    key: 'publishers',
    endpoint: `${API_URL}/me/following/publishers`,
    emptyMessageKey: 'noPublishers',
    unitLabel: 'publisher',
    mapper: (data) => mapApiPublishers(data as ApiPublisher[]),
  },
]

const EMPTY_GROUPS: Record<RelationshipGroupKey, GroupState> = {
  followers: { items: [], error: null },
  following: { items: [], error: null },
  publishers: { items: [], error: null },
}

export default function Followers() {
  const { t } = useTranslation()
  const apiFetch = useApiFetch()
  const [groups, setGroups] = useState<Record<RelationshipGroupKey, GroupState>>(EMPTY_GROUPS)
  const [loading, setLoading] = useState(true)
  const [moreGroup, setMoreGroup] = useState<RelationshipGroupKey | null>(null)

  const moreGroupConfig = useMemo(
    () => GROUPS.find((group) => group.key === moreGroup) ?? null,
    [moreGroup]
  )

  const loadFollowers = useCallback(async () => {
    setLoading(true)

    try {
      const responses = await Promise.all(GROUPS.map((group) => apiFetch(group.endpoint)))

      if (responses.some((response) => response.status === 401)) {
        setGroups(
          GROUPS.reduce(
            (acc, group) => {
              acc[group.key] = { items: [], error: t('followers.loginForConnections') }
              return acc
            },
            {} as Record<RelationshipGroupKey, GroupState>
          )
        )
        return
      }

      const next = {} as Record<RelationshipGroupKey, GroupState>
      for (let i = 0; i < GROUPS.length; i++) {
        const group = GROUPS[i]
        const response = responses[i]

        if (!response.ok) {
          next[group.key] = {
            items: [],
            error: t('followers.unableToLoad', { label: t(`followers.${group.key}`) }),
          }
          continue
        }

        const data = await response.json()
        next[group.key] = { items: group.mapper(data), error: null }
      }
      setGroups(next)
    } catch {
      setGroups(
        GROUPS.reduce(
          (acc, group) => {
            acc[group.key] = {
              items: [],
              error: t('followers.unableToLoad', { label: t(`followers.${group.key}`) }),
            }
            return acc
          },
          {} as Record<RelationshipGroupKey, GroupState>
        )
      )
    } finally {
      setLoading(false)
    }
  }, [apiFetch, t])

  useEffect(() => {
    const run = async () => {
      await loadFollowers()
    }

    void run()
  }, [loadFollowers])

  useEffect(() => {
    const handleAuthChange = () => {
      void loadFollowers()
    }

    window.addEventListener('storage', handleAuthChange)
    window.addEventListener(AUTH_CHANGED_EVENT, handleAuthChange)
    return () => {
      window.removeEventListener('storage', handleAuthChange)
      window.removeEventListener(AUTH_CHANGED_EVENT, handleAuthChange)
    }
  }, [loadFollowers])

  if (loading) {
    return (
      <div className="space-y-2 px-2 py-1">
        <div className="h-20 animate-pulse rounded-xl bg-white/5" />
        <div className="h-20 animate-pulse rounded-xl bg-white/5" />
      </div>
    )
  }

  return (
    <>
      <div className="space-y-2 px-2 py-1">
        {GROUPS.map((group) => {
          const items = groups[group.key].items
          const preview = items.slice(0, 3)
          const hasMore = items.length > 3

          return (
            <Card key={group.key} className="border-white/10 bg-white/5">
              <CardContent className="space-y-3 px-3 py-3">
                <div className="flex items-center justify-between">
                  <div>
                    <div className="text-sm font-semibold text-white">
                      {t(`followers.${group.key}`)}
                    </div>
                    <div className="text-xs text-white/50">
                      {items.length} {group.unitLabel}
                      {items.length === 1 ? '' : 's'}
                    </div>
                  </div>
                </div>

                {groups[group.key].error ? (
                  <div className="text-xs text-white/60">{groups[group.key].error}</div>
                ) : preview.length > 0 ? (
                  <div className="space-y-2">
                    {preview.map((item) => (
                      <Link
                        key={item.id}
                        to={item.linkTo}
                        className="flex items-center gap-3 rounded-lg px-2 py-2 transition-colors hover:bg-white/10 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-white/30"
                      >
                        <Avatar className="h-9 w-9">
                          {item.avatarFilename ? (
                            <AvatarImage
                              src={authUrl(`/auth/users/${item.id}/avatar`)}
                              alt={item.displayName}
                            />
                          ) : null}
                          <AvatarFallback>{item.initials}</AvatarFallback>
                          {item.isOnline && <AvatarBadge className="bg-green-500" />}
                        </Avatar>
                        <div className="min-w-0 flex-1">
                          <div className="truncate text-sm font-medium text-white">
                            {item.displayName}
                          </div>
                          <div className="truncate text-xs text-white/50">{item.subtitle}</div>
                        </div>
                      </Link>
                    ))}

                    {hasMore && (
                      <Button
                        type="button"
                        variant="ghost"
                        className="h-8 w-full justify-start px-2 text-xs text-white/70 hover:bg-white/10 hover:text-white"
                        onClick={() => setMoreGroup(group.key)}
                      >
                        More {items.length - 3}
                      </Button>
                    )}
                  </div>
                ) : (
                  <div className="text-xs text-white/60">
                    {t(`followers.${group.emptyMessageKey}`)}
                  </div>
                )}
              </CardContent>
            </Card>
          )
        })}
      </div>

      <Dialog open={moreGroup !== null} onOpenChange={(open) => !open && setMoreGroup(null)}>
        <DialogContent className="max-h-[80vh] max-w-4xl overflow-hidden border-white/10 bg-slate-950 text-white sm:max-w-4xl">
          <DialogHeader className="border-b border-white/10 pb-4">
            <DialogTitle className="text-white">
              {moreGroupConfig ? t(`followers.${moreGroupConfig.key}`) : t('followers.followers')}
            </DialogTitle>
          </DialogHeader>

          <div className="max-h-[65vh] overflow-y-auto px-1 py-1">
            <div className="grid grid-cols-2 gap-4 sm:grid-cols-3 lg:grid-cols-4 xl:grid-cols-5">
              {(moreGroupConfig ? groups[moreGroupConfig.key].items.slice(0, 20) : []).map(
                (item) => (
                  <Link
                    key={item.id}
                    to={item.linkTo}
                    className="flex flex-col items-center gap-2 rounded-xl border border-white/10 bg-white/5 p-3 text-center transition-colors hover:bg-white/10 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-white/30"
                  >
                    <Avatar className="h-14 w-14">
                      {item.avatarFilename ? (
                        <AvatarImage
                          src={authUrl(`/auth/users/${item.id}/avatar`)}
                          alt={item.displayName}
                        />
                      ) : null}
                      <AvatarFallback>{item.initials}</AvatarFallback>
                      {item.isOnline && <AvatarBadge className="bg-green-500" />}
                    </Avatar>
                    <div className="min-w-0">
                      <div className="truncate text-sm font-medium text-white">
                        {item.displayName}
                      </div>
                    </div>
                  </Link>
                )
              )}
            </div>

            {(moreGroupConfig ? groups[moreGroupConfig.key].items.slice(0, 20) : []).length ===
              0 && <div className="px-2 py-6 text-sm text-white/60">No items to show.</div>}
          </div>
        </DialogContent>
      </Dialog>
    </>
  )
}
