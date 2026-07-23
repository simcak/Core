import { useEffect, useState } from 'react'
import { useTranslation } from 'react-i18next'
import { AUTH_CHANGED_EVENT, authUrl } from '../../utils/auth'
import { useApiFetch } from '../../hooks/useApiFetch'
import { Button } from '../ui/button'
import { Input } from '../ui/input'
import { Label } from '../ui/label'
import { Avatar, AvatarBadge, AvatarFallback, AvatarImage } from '../ui/avatar'
import { Edit2, Check, X, User } from 'lucide-react'

type ProfileUser = {
  username: string
  email: string
  firstName?: string | null
  lastName?: string | null
  roleName: string
  phone?: string | null
  status: string
  emailVerified: boolean
  createdAt: string
  avatarFilename?: string | null
  isOnline?: boolean
}

type ProfileProps = {
  user: ProfileUser
  onProfileUpdated?: () => void | Promise<void>
}

function ProfileField({ label, value }: { label: string; value: string }) {
  return (
    <div className="flex flex-col gap-1">
      <Label className="text-[10px] font-semibold text-white/50 uppercase tracking-wide">
        {label}
      </Label>
      <span className="text-sm text-white/90 font-medium break-words">{value}</span>
    </div>
  )
}

function EditableField({
  label,
  value,
  onChange,
}: {
  label: string
  value: string
  onChange: (v: string) => void
}) {
  return (
    <div className="flex flex-col gap-1">
      {label ? (
        <Label className="text-[10px] font-semibold text-white/60 uppercase tracking-wide">
          {label}
        </Label>
      ) : null}
      <Input
        value={value}
        onChange={(e) => onChange(e.target.value)}
        className="bg-white/6 border-white/12 text-white text-sm"
      />
    </div>
  )
}

export default function Profile({ user, onProfileUpdated }: ProfileProps) {
  const { t } = useTranslation()
  const fullName =
    [user.firstName, user.lastName].filter(Boolean).join(' ') || t('profile.notProvided')
  const apiFetch = useApiFetch()

  const [isEditing, setIsEditing] = useState(false)
  const [isProfileOpen, setIsProfileOpen] = useState(false)
  const [avatarFile, setAvatarFile] = useState<File | null>(null)
  const [avatarPreview, setAvatarPreview] = useState<string | null>(null)

  const [formData, setFormData] = useState({
    firstName: user.firstName ?? '',
    lastName: user.lastName ?? '',
    phone: user.phone ?? '',
    avatarFilename: user.avatarFilename ?? '',
  })

  useEffect(() => {
    return () => {
      if (avatarPreview?.startsWith('blob:')) {
        URL.revokeObjectURL(avatarPreview)
      }
    }
  }, [avatarPreview])

  function handleEditClick() {
    setFormData({
      firstName: user.firstName ?? '',
      lastName: user.lastName ?? '',
      phone: user.phone ?? '',
      avatarFilename: user.avatarFilename ?? '',
    })
    setAvatarFile(null)
    setAvatarPreview(null)
    setIsEditing(true)
  }

  function handleFieldChange<K extends keyof typeof formData>(key: K, value: string) {
    setFormData((s) => ({ ...s, [key]: value }))
  }

  function handleAvatarChange(event: React.ChangeEvent<HTMLInputElement>) {
    const file = event.target.files?.[0] ?? null
    setAvatarFile(file)

    if (avatarPreview?.startsWith('blob:')) {
      URL.revokeObjectURL(avatarPreview)
    }

    if (file) {
      setAvatarPreview(URL.createObjectURL(file))
    } else {
      setAvatarPreview(null)
    }
  }

  async function saveChanges() {
    try {
      const response = await apiFetch(authUrl('/auth/editProfile'), {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          first_name: formData.firstName || null,
          last_name: formData.lastName || null,
          phone: formData.phone || null,
          avatar_filename: formData.avatarFilename || null,
        }),
      })

      if (!response.ok) {
        throw new Error('Failed to update profile')
      }

      if (avatarFile) {
        const fd = new FormData()
        fd.append('file', avatarFile)
        const avatarResponse = await apiFetch(authUrl('/auth/me/avatar'), {
          method: 'POST',
          body: fd,
        })

        if (!avatarResponse.ok) {
          throw new Error('Failed to upload avatar')
        }
      }

      window.dispatchEvent(new Event(AUTH_CHANGED_EVENT))
      if (onProfileUpdated) {
        await onProfileUpdated()
      }
      setIsEditing(false)
      setIsProfileOpen(false)
    } catch (error) {
      console.error('Error saving profile:', error)
      setIsEditing(false)
      setIsProfileOpen(false)
    }
  }

  function cancelChanges() {
    setFormData({
      firstName: user.firstName ?? '',
      lastName: user.lastName ?? '',
      phone: user.phone ?? '',
      avatarFilename: user.avatarFilename ?? '',
    })
    setIsEditing(false)
    setIsProfileOpen(false)
  }

  return (
    <div className="grid gap-0">
      {/* Profile Header - Clickable Toggle with Icon */}
      <button
        onClick={() => setIsProfileOpen(!isProfileOpen)}
        className="flex items-center justify-between w-full px-2 py-1 text-xs font-semibold text-white/70 hover:text-white transition-colors"
        aria-expanded={isProfileOpen}
      >
        <div className="flex items-center gap-2">
          <div className="p-1 bg-white/10 rounded-sm flex items-center justify-center">
            <User className="w-3.5 h-3.5 text-white/80" />
          </div>
          <span>{t('profile.title')}</span>
        </div>
        <svg
          width="16"
          height="16"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          className={`transition-transform ${isProfileOpen ? 'rotate-180' : 'rotate-0'}`}
        >
          <polyline points="6 9 12 15 18 9"></polyline>
        </svg>
      </button>

      {/* Profile Details - Only Visible When Open */}
      {isProfileOpen && (
        <div className="grid gap-3 p-2">
          <div className="grid grid-cols-1 gap-3">
            {isEditing ? (
              <>
                <EditableField
                  label={t('profile.firstName')}
                  value={formData.firstName}
                  onChange={(v) => handleFieldChange('firstName', v)}
                />
                <EditableField
                  label={t('profile.lastName')}
                  value={formData.lastName}
                  onChange={(v) => handleFieldChange('lastName', v)}
                />
              </>
            ) : (
              <>
                <ProfileField label={t('profile.fullName')} value={fullName} />
                <ProfileField label={t('profile.role')} value={user.roleName} />
              </>
            )}
            <ProfileField label={t('profile.email')} value={user.email} />
            {isEditing ? (
              <EditableField
                label={t('profile.phone')}
                value={formData.phone}
                onChange={(v) => handleFieldChange('phone', v)}
              />
            ) : (
              <ProfileField
                label={t('profile.phone')}
                value={user.phone || t('profile.notProvided')}
              />
            )}
            <ProfileField label={t('profile.status')} value={user.status} />
            <ProfileField label={t('profile.verified')} value={user.emailVerified ? 'Yes' : 'No'} />
          </div>

          <div className="pt-2 border-t border-white/6 grid gap-1">
            <span className="text-[11px] font-semibold text-white/50 uppercase tracking-wider">
              {t('profile.createdAt')}
            </span>
            <span className="text-sm text-white/80 font-medium">{user.createdAt}</span>
          </div>

          <div className="pt-2 border-t border-white/6 grid gap-1">
            <span className="text-[11px] font-semibold text-white/50 uppercase tracking-wider">
              {t('profile.avatar')}
            </span>
            <div className="flex items-center gap-3">
              <Avatar className="h-10 w-10">
                {avatarPreview ? (
                  <AvatarImage src={avatarPreview} alt="Selected avatar preview" />
                ) : user.avatarFilename ? (
                  <AvatarImage src={authUrl('/auth/me/avatar')} alt="Current avatar" />
                ) : null}
                <AvatarFallback>
                  {(
                    (user.firstName?.[0] ?? '') + (user.lastName?.[0] ?? '') ||
                    user.username.slice(0, 2)
                  ).toUpperCase()}
                </AvatarFallback>
                {user.isOnline && <AvatarBadge className="bg-green-500" />}
              </Avatar>
              <div className="flex-1 grid gap-2">
                {isEditing ? (
                  <Input
                    type="file"
                    accept="image/jpeg,image/png,image/webp"
                    onChange={handleAvatarChange}
                    className="bg-white/6 border-white/12 text-white text-sm"
                  />
                ) : (
                  <span className="text-sm text-white/80 font-medium">
                    {user.avatarFilename || t('profile.noAvatar')}
                  </span>
                )}
              </div>
            </div>
          </div>

          <div className="grid gap-2">
            <div className="flex items-center gap-2">
              {!isEditing ? (
                <Button onClick={handleEditClick} variant="ghost" size="sm" className="gap-2">
                  <Edit2 className="h-4 w-4" />
                  {t('profile.editProfile')}
                </Button>
              ) : (
                <>
                  <Button onClick={saveChanges} size="sm" className="gap-2">
                    <Check className="h-4 w-4" />
                    {t('profile.save')}
                  </Button>
                  <Button onClick={cancelChanges} variant="outline" size="sm" className="gap-2">
                    <X className="h-4 w-4" />
                    {t('profile.cancel')}
                  </Button>
                </>
              )}
            </div>
          </div>
        </div>
      )}
    </div>
  )
}
