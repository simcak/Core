import { useCallback, useEffect, useState } from 'react'
import { Link } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import Subscription from '../components/settings/Subscription.tsx'
import Followers from '../components/settings/Followers.tsx'
import Profile from '../components/settings/Profile.tsx'
import LogOut from '../components/settings/LogOut.tsx'
import { AUTH_CHANGED_EVENT } from '../utils/auth.ts'
import { useApiFetch } from '../hooks/useApiFetch.ts'
import { useAuth } from '../hooks/useAuth.ts'
import { Button } from '../components/ui/button.tsx'
import {
  Sidebar,
  SidebarContent,
  SidebarFooter,
  SidebarHeader,
  SidebarGroup,
  SidebarGroupLabel,
  SidebarGroupContent,
  SidebarMenu,
  SidebarMenuItem,
  SidebarRail,
} from '../components/ui/sidebar.tsx'
import {
  ChevronDown,
  ChevronRight,
  CreditCard,
  Globe,
  Settings,
  UserRoundKey,
  Users,
} from 'lucide-react'

const LANGUAGES = [
  { code: 'en', label: 'English' },
  { code: 'ar', label: 'العربية' },
  { code: 'cs', label: 'Čeština' },
]

type ApiUser = {
  username: string
  email: string
  first_name?: string | null
  last_name?: string | null
  phone?: string | null
  role?: { role_name?: string | null }
  status?: string | null
  email_verified?: boolean | null
  created_at?: string | null
  updated_at?: string | null
  avatar_filename?: string | null
  is_online?: boolean
}

const mapUser = (user: ApiUser) => ({
  username: user.username,
  email: user.email,
  firstName: user.first_name ?? null,
  lastName: user.last_name ?? null,
  roleName: user.role?.role_name ?? 'user',
  phone: user.phone ?? null,
  status: user.status ?? 'active',
  emailVerified: user.email_verified ?? false,
  createdAt: user.created_at ?? 'Unknown',
  updatedAt: user.updated_at ?? 'Unknown',
  avatarFilename: user.avatar_filename ?? null,
  isOnline: user.is_online ?? false,
})

export default function AppSidebar() {
  const { t, i18n } = useTranslation()
  const isRTL = i18n.language === 'ar'
  const apiFetch = useApiFetch()
  const { token } = useAuth()
  const [currentUser, setCurrentUser] = useState<ApiUser | null>(null)
  const [loading, setLoading] = useState(true)
  const [openedSections, setOpenedSections] = useState<Record<string, boolean>>({
    subscription: false,
    followers: false,
    profile: true,
  })

  const toggleSection = (section: string) => {
    setOpenedSections((prev) => ({
      ...prev,
      [section]: !prev[section],
    }))
  }

  const loadProfile = useCallback(async () => {
    if (!token) {
      setCurrentUser(null)
      setLoading(false)
      return
    }

    setLoading(true)
    try {
      const response = await apiFetch(`/auth/me`)
      if (!response.ok) {
        setCurrentUser(null)
        return
      }

      const data = (await response.json()) as ApiUser
      setCurrentUser(data)
    } catch {
      setCurrentUser(null)
    } finally {
      setLoading(false)
    }
  }, [apiFetch, token])

  useEffect(() => {
    if (!token) {
      return
    }

    let mounted = true

    const load = async () => {
      setLoading(true)
      try {
        const response = await apiFetch(`/auth/me`)
        if (!mounted) return
        if (!response.ok) {
          setCurrentUser(null)
          return
        }

        const data = (await response.json()) as ApiUser
        if (mounted) {
          setCurrentUser(data)
        }
      } catch {
        if (mounted) {
          setCurrentUser(null)
        }
      } finally {
        if (mounted) {
          setLoading(false)
        }
      }
    }

    void load()

    return () => {
      mounted = false
    }
  }, [apiFetch, token])

  useEffect(() => {
    const handleAuthChange = () => {
      void loadProfile()
    }

    window.addEventListener('storage', handleAuthChange)
    window.addEventListener(AUTH_CHANGED_EVENT, handleAuthChange)
    return () => {
      window.removeEventListener('storage', handleAuthChange)
      window.removeEventListener(AUTH_CHANGED_EVENT, handleAuthChange)
    }
  }, [loadProfile])

  if (!token || (!loading && !currentUser)) {
    return (
      <Sidebar
        side="right"
        collapsible="offcanvas"
        dir={isRTL ? 'rtl' : 'ltr'}
        className="border-l border-white/10 bg-[#111]"
      >
        <SidebarHeader className="border-b border-white/10 py-2">
          <div className="flex items-center gap-2 px-2">
            <Settings className="h-4 w-4 text-white/60" />
            <span className="text-xs font-semibold text-white/60">{t('appSidebar.settings')}</span>
          </div>
        </SidebarHeader>

        <SidebarContent className="flex flex-col gap-3 px-3 pt-4 pb-6">
          <div className="w-full max-w-60 rounded-2xl border border-white/10 bg-white/5 p-4 text-center shadow-lg shadow-black/20 backdrop-blur-sm">
            <div className="mx-auto mb-3 flex h-10 w-10 items-center justify-center rounded-full bg-white/10 text-white/90">
              <Settings className="h-4 w-4" />
            </div>
            <div className="space-y-1">
              <p className="text-sm font-semibold text-white">{t('appSidebar.signInToContinue')}</p>
              <p className="text-xs leading-5 text-white/60">{t('appSidebar.viewProfile')}</p>
            </div>
            <Button asChild className="mt-4 w-full">
              <Link to="/login">{t('appSidebar.logIn')}</Link>
            </Button>
          </div>

          <div className="w-full">
            <div className="flex items-center gap-2 px-2 pb-1.5 text-xs font-semibold text-white/70">
              <div className="rounded bg-white/10 p-0.5">
                <Globe className="h-3.5 w-3.5" />
              </div>
              <span>{t('language.switcher')}</span>
            </div>
            <div className="flex gap-1">
              {LANGUAGES.map((l) => (
                <button
                  key={l.code}
                  type="button"
                  onClick={() => void i18n.changeLanguage(l.code)}
                  className={`flex-1 rounded-lg py-1.5 px-1 text-xs transition-colors ${
                    i18n.language === l.code
                      ? 'bg-orange-500/20 font-semibold text-orange-400'
                      : 'text-white/50 hover:bg-white/5 hover:text-white'
                  }`}
                >
                  {l.label}
                </button>
              ))}
            </div>
          </div>
        </SidebarContent>

        <SidebarRail />
      </Sidebar>
    )
  }

  return (
    <Sidebar
      side="right"
      collapsible="offcanvas"
      dir={isRTL ? 'rtl' : 'ltr'}
      className="border-l border-white/10 bg-[#111]"
    >
      <SidebarHeader className="border-b border-white/10 py-2">
        <div className="flex items-center gap-2 px-2">
          <Settings className="h-4 w-4 text-white/60" />
          <span className="text-xs font-semibold text-white/60">{t('appSidebar.settings')}</span>
        </div>
      </SidebarHeader>

      <SidebarContent className="py-2">
        <div className="flex min-h-0 flex-1 flex-col gap-3 px-1.5">
          <SidebarGroup className="p-0">
            <SidebarGroupLabel asChild>
              <button
                onClick={() => toggleSection('subscription')}
                className="flex w-full items-center justify-between px-2 py-1.5 text-xs font-semibold text-white/70 transition-colors hover:text-white"
              >
                <div className="flex items-center gap-2">
                  <div className="rounded bg-white/10 p-0.5">
                    <CreditCard className="h-3.5 w-3.5" />
                  </div>
                  <span>{t('appSidebar.subscription')}</span>
                </div>
                <ChevronDown
                  className={`h-4 w-4 transition-transform ${
                    openedSections.subscription ? 'rotate-180' : ''
                  }`}
                />
              </button>
            </SidebarGroupLabel>

            {openedSections.subscription && (
              <SidebarGroupContent className="pt-1">
                <Subscription />
              </SidebarGroupContent>
            )}
          </SidebarGroup>

          <SidebarGroup className="p-0">
            <SidebarGroupLabel asChild>
              <div className="flex w-full items-center gap-2 px-2 py-1.5 text-xs font-semibold text-white/70">
                <div className="rounded bg-white/10 p-0.5">
                  <Globe className="h-3.5 w-3.5" />
                </div>
                <span>{t('language.switcher')}</span>
              </div>
            </SidebarGroupLabel>
            <SidebarGroupContent className="px-2 pt-1 pb-1">
              <div className="flex gap-1">
                {LANGUAGES.map((l) => (
                  <button
                    key={l.code}
                    type="button"
                    onClick={() => void i18n.changeLanguage(l.code)}
                    className={`flex-1 rounded-lg py-1.5 px-1 text-xs transition-colors ${
                      i18n.language === l.code
                        ? 'bg-orange-500/20 font-semibold text-orange-400'
                        : 'text-white/50 hover:bg-white/5 hover:text-white'
                    }`}
                  >
                    {l.label}
                  </button>
                ))}
              </div>
            </SidebarGroupContent>
          </SidebarGroup>

          <SidebarGroup className="p-0">
            <SidebarGroupContent className="pt-1">
              {currentUser ? (
                <Profile user={mapUser(currentUser)} onProfileUpdated={loadProfile} />
              ) : (
                <span className="block px-1 py-3 text-sm text-white/60">
                  {loading ? t('appSidebar.loading') : t('appSidebar.loginForProfile')}
                </span>
              )}
            </SidebarGroupContent>
          </SidebarGroup>

          <SidebarGroup className="p-0">
            <SidebarGroupLabel asChild>
              <button
                onClick={() => toggleSection('followers')}
                className="flex w-full items-center justify-between px-2 py-1.5 text-xs font-semibold text-white/70 transition-colors hover:text-white"
              >
                <div className="flex items-center gap-2">
                  <div className="rounded bg-white/10 p-0.5">
                    <Users className="h-3.5 w-3.5" />
                  </div>
                  <span>{t('appSidebar.followers')}</span>
                </div>
                <ChevronDown
                  className={`h-4 w-4 transition-transform ${
                    openedSections.followers ? 'rotate-180' : ''
                  }`}
                />
              </button>
            </SidebarGroupLabel>

            {openedSections.followers && (
              <SidebarGroupContent className="pt-1 px-2">
                <Followers />
              </SidebarGroupContent>
            )}
          </SidebarGroup>

          <SidebarGroup className="p-0">
            {currentUser?.role?.role_name === 'admin' && (
              <SidebarGroupLabel asChild>
                <button className="flex w-full items-center justify-between px-2 py-1.5 text-xs font-semibold text-white/70 transition-colors hover:text-white">
                  <div className="flex items-center gap-2">
                    <div className="rounded bg-white/10 p-0.5">
                      <UserRoundKey className="h-3.5 w-3.5" />
                    </div>
                    <Link to="/admin">{t('appSidebar.adminPanel')}</Link>
                  </div>
                  <ChevronRight
                    className={`h-4 w-4 transition-transform ${isRTL ? 'scale-x-[-1]' : ''}`}
                  />
                </button>
              </SidebarGroupLabel>
            )}
          </SidebarGroup>
        </div>
      </SidebarContent>

      <SidebarFooter className="border-t border-white/10 py-2">
        <SidebarMenu>
          <SidebarMenuItem>
            <LogOut />
          </SidebarMenuItem>
        </SidebarMenu>
      </SidebarFooter>

      <SidebarRail />
    </Sidebar>
  )
}
