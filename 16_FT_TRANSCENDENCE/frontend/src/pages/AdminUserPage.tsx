import { useState, useEffect } from 'react'
import { Link, useNavigate, useParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { Button } from '@/components/ui/button.tsx'
import { Input } from '@/components/ui/input.tsx'
import { Label } from '@/components/ui/label.tsx'
import ConfirmDisableDialog from '@/components/common/ConfirmDisableDialog.tsx'
import ConfirmDeleteDialog from '@/components/common/ConfirmDeleteDialog.tsx'
import ConfirmEnableDialog from '@/components/common/ConfirmEnableDialog.tsx'
import { authUrl } from '@/utils/auth.ts'                                    // new
import { Avatar, AvatarFallback, AvatarImage } from '@/components/ui/avatar.tsx'  // new

type FormState = {
  id: number
  username: string
  email: string
  first_name: string | null
  last_name: string | null
  phone: string | null
  password: string
  role_id: number
  created_at: string
  updated_at: string
  last_login_at: string | null
  status: string
  avatar_filename: string | null
}

export default function AdminUserPage() {
  const { t } = useTranslation()
  const { userId } = useParams<{ userId: string }>()
  const navigate = useNavigate()
  const apiFetch = useApiFetch()
  const [form, setForm] = useState<FormState>({
    id: 0,
    username: '',
    email: '',
    first_name: '',
    last_name: '',
    phone: '',
    password: '',
    role_id: 0,
    created_at: '',
    updated_at: '',
    last_login_at: '',
    status: '',
    avatar_filename: null,
  })

  const setField = (field: keyof FormState, value: string | null) =>
    setForm((prev) => ({ ...prev, [field]: value }))

  const [isSubmitting, setIsSubmitting] = useState(false)
  const [error, setError] = useState<string | null>(null)
  const [roles, setRoles] = useState<{ id: number; role_name: string }[]>([])
  const [disableUserOpen, setDisableUserOpen] = useState(false)
  const [isDisablingUser, setIsDisablingUser] = useState(false)
  const [deleteUserOpen, setDeleteUserOpen] = useState(false)
  const [isDeletingUser, setIsDeletingUser] = useState(false)
  const [enableUserOpen, setEnableUserOpen] = useState(false)
  const [isEnablingUser, setIsEnablingUser] = useState(false)
  const [avatarFile, setAvatarFile] = useState<File | null>(null)
  const [avatarPreview, setAvatarPreview] = useState<string | null>(null)
  const [isUploadingAvatar, setIsUploadingAvatar] = useState(false)
  const [avatarError, setAvatarError] = useState<string | null>(null)

  useEffect(() => {
    Promise.all([
      apiFetch(`/auth/admin/users/${userId}`).then((r) => r.json()),
      apiFetch('/auth/roles').then((r) => r.json()),
    ]).then(([userData, rolesData]) => {
      //setUser(userData)
      //const t = userData.translations[0]
      setForm({
        id: userData.id,
        username: userData.username,
        email: userData.email,
        first_name: userData.first_name,
        last_name: userData.last_name,
        phone: userData.phone,
        password: '', // never pre-fill password
        role_id: userData.role_id,
        created_at: userData.created_at,
        updated_at: userData.updated_at,
        last_login_at: userData.last_login_at,
        status: userData.status,
        avatar_filename: userData.avatar_filename ?? null,
      })
      setRoles(rolesData)
      //setLoading(false)
    })
  }, [apiFetch, userId])


  useEffect(() => {
    return () => {
      if (avatarPreview?.startsWith('blob:')) {
        URL.revokeObjectURL(avatarPreview)
      }
    }
  }, [avatarPreview])
 
  const handleAvatarChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files?.[0] ?? null
    setAvatarFile(file)
    setAvatarError(null)
 
    if (avatarPreview?.startsWith('blob:')) {
      URL.revokeObjectURL(avatarPreview)
    }
 
    if (file) {
      setAvatarPreview(URL.createObjectURL(file))
    } else {
      setAvatarPreview(null)
    }
  }
 
  const handleAvatarUpload = async () => {
    if (!avatarFile) return
    setIsUploadingAvatar(true)
    setAvatarError(null)
    try {
      const fd = new FormData()
      fd.append('file', avatarFile)
      const res = await apiFetch(`/auth/admin/users/${form.id}/avatar`, {
        method: 'POST',
        body: fd,
      })
      if (!res.ok) {
        throw new Error(`Failed to upload avatar: ${res.status}`)
      }
      const data = await res.json()
      setField('avatar_filename', data.avatar_filename)
      setAvatarFile(null)
      if (avatarPreview?.startsWith('blob:')) {
        URL.revokeObjectURL(avatarPreview)
      }
      setAvatarPreview(null)
    } catch (e) {
      setAvatarError(String(e))
    } finally {
      setIsUploadingAvatar(false)
    }
  }


  const handleAvatarDelete = async () => {
    if (!form.avatar_filename) return
    setIsUploadingAvatar(true)
    setAvatarError(null)
    try {
      const res = await apiFetch(`/auth/admin/users/${form.id}/avatar`, {
        method: 'DELETE',
      })
      if (!res.ok) {
        throw new Error(`Failed to remove avatar: ${res.status}`)
      }
      setField('avatar_filename', null)
      setAvatarFile(null)
      if (avatarPreview?.startsWith('blob:')) {
        URL.revokeObjectURL(avatarPreview)
      }
      setAvatarPreview(null)
    } catch (e) {
      setAvatarError(String(e))
    } finally {
      setIsUploadingAvatar(false)
    }
  }



  const handleEnableUser = async () => {
    setIsEnablingUser(true)
    try {
      const res = await apiFetch(`/auth/admin/users/${userId}/enable`, { method: 'PATCH' })
      if (!res.ok) throw new Error(`Enable failed: ${res.status}`)
      navigate('/admin')
    } catch (e) {
      console.error(e)
      setIsEnablingUser(false)
    }
  }

  const handleDisableUser = async () => {
    setIsDisablingUser(true)
    try {
      const res = await apiFetch(`/auth/admin/users/${userId}/disable`, { method: 'PATCH' })
      if (!res.ok) throw new Error(`Disable failed: ${res.status}`)
      navigate('/admin/')
    } catch (e) {
      console.error(e)
      setIsDisablingUser(false)
    }
  }

  const handleDeleteUser = async () => {
    setIsDeletingUser(true)
    try {
      const res = await apiFetch(`/auth/admin/users/${userId}`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Delete failed: ${res.status}`)
      navigate('/admin/')
    } catch (e) {
      console.error(e)
      setIsDeletingUser(false)
    }
  }



  const handleSubmit = async () => {
    if (!form.username || !form.email) {
      setError(t('admin.users.usernameRequired'))
      return
    }
    setIsSubmitting(true)
    setError(null)
    try {
      const UserRes = await apiFetch(`/auth/admin/users/${form.id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          username: form.username,
          email: form.email,
          first_name: form.first_name,
          last_name: form.last_name,
          role_id: form.role_id,
          phone: form.phone || null,
          password: form.password,
        }),
      })
      if (!UserRes.ok) {
        if (UserRes.status === 409) {
          const data = await UserRes.json()
          setError(data.detail) // "Username is already taken" or "Email is already taken"
        } else {
          throw new Error(`Failed to create user: ${UserRes.status}`)
        }
        return
      }
      //const user = await UserRes.json()
      navigate(`/admin/`)
    } catch (e) {
      setError(String(e))
    } finally {
      setIsSubmitting(false)
    }
  }

  return (
    <div className="flex flex-col gap-8 max-w-3xl">
      <div className="flex items-start justify-between">
        <div className="flex flex-col gap-1">
          <Button
            variant="ghost"
            size="sm"
            asChild
            className="-ml-2 w-fit text-muted-foreground hover:text-foreground"
          >
            <Link to="/admin">{t('admin.users.backToUsers')}</Link>
          </Button>
          <h1 className="text-2xl font-bold tracking-tight">
            {t('admin.users.editUser', { username: form.username })}
          </h1>
          <p className="text-sm text-muted-foreground">
            {t('admin.users.statusLabel', { status: form.status })}
          </p>
        </div>

        {form.status === 'disabled' ? (
          <Button
            variant="outline"
            size="sm"
            onClick={() => setEnableUserOpen(true)}
            className="btn-success"
          >
            {t('admin.users.activateUser')}
          </Button>
        ) : (
          <Button variant="outline" size="sm" onClick={() => setDisableUserOpen(true)}>
            {t('admin.users.disableUser')}
          </Button>
        )}
      </div>

      {error && <p className="text-sm text-destructive">{error}</p>}

      <div className="grid grid-cols-2 gap-4">
        <div className="col-span-2 flex flex-col gap-1.5">
          <Label>{t('admin.users.username')}</Label>
          <Input value={form.username} onChange={(e) => setField('username', e.target.value)} />
        </div>

        <div className="col-span-2 flex flex-col gap-1.5">
          <Label>{t('admin.users.email')}</Label>
          <Input value={form.email ?? ''} onChange={(e) => setField('email', e.target.value)} />
        </div>

        <div className="col-span-2 flex flex-col gap-1.5">
          <Label>{t('admin.users.password')}</Label>
          <Input
            value={form.password ?? ''}
            onChange={(e) => setField('password', e.target.value)}
          />
        </div>

        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.users.firstName')}</Label>
          <Input
            value={form.first_name ?? ''}
            onChange={(e) => setField('first_name', e.target.value)}
          />
        </div>

        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.users.lastName')}</Label>
          <Input
            value={form.last_name ?? ''}
            onChange={(e) => setField('last_name', e.target.value)}
          />
        </div>

        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.users.phone')}</Label>
          <Input value={form.phone ?? ''} onChange={(e) => setField('phone', e.target.value)} />
        </div>
      </div>

      <div className="flex flex-col gap-1.5">
        <Label>{t('admin.users.role')}</Label>
        <select
          value={form.role_id}
          onChange={(e) => setForm((prev) => ({ ...prev, role_id: parseInt(e.target.value) }))}
          className="border rounded px-3 py-2 text-sm"
        >
          {roles.map((r) => (
            <option key={r.id} value={r.id}>
              {r.role_name.charAt(0).toUpperCase() + r.role_name.slice(1)}
            </option>
          ))}
        </select>
      </div>



      <div className="flex flex-col gap-1.5">
        <Label>{t('admin.users.avatar')}</Label>
        <div className="flex items-center gap-4">
          <Avatar className="h-14 w-14">
            {avatarPreview ? (
              <AvatarImage src={avatarPreview} alt="Selected avatar preview" />
            ) : form.avatar_filename ? (
              <AvatarImage src={authUrl(`/auth/users/${form.id}/avatar`)} alt="Current avatar" />
            ) : null}
            <AvatarFallback>
              {((form.first_name?.[0] ?? '') + (form.last_name?.[0] ?? '') || form.username.slice(0, 2)).toUpperCase()}
            </AvatarFallback>
          </Avatar>
          <div className="flex-1 flex flex-col gap-2">
            <Input
              type="file"
              accept="image/jpeg,image/png,image/webp"
              onChange={handleAvatarChange}
            />
            {avatarFile && (
              <Button
                type="button"
                size="sm"
                onClick={handleAvatarUpload}
                disabled={isUploadingAvatar}
                className="w-fit"
              >
                {isUploadingAvatar ? t('admin.users.uploadingAvatar') : t('admin.users.uploadAvatar')}
              </Button>
            )}
            {!avatarFile && form.avatar_filename && (
              <Button
                type="button"
                variant="outline"
                size="sm"
                onClick={handleAvatarDelete}
                disabled={isUploadingAvatar}
                className="w-fit text-destructive hover:text-destructive"
              >
                {isUploadingAvatar ? t('admin.users.removingAvatar') : t('admin.users.removeAvatar')}
              </Button>
            )}
            {avatarError && <p className="text-sm text-destructive">{avatarError}</p>}
          </div>
        </div>
      </div>



      <div className="flex gap-3">
        <Button variant="outline" onClick={() => navigate('/admin/')} disabled={isSubmitting}>
          {t('admin.users.cancel')}
        </Button>
        <Button onClick={handleSubmit} disabled={isSubmitting}>
          {isSubmitting ? t('admin.users.saving') : t('admin.users.editUserBtn')}
        </Button>
      </div>

      {/* Danger Zone */}
      <div className="danger-zone">
        <div className="danger-zone-header">
          <h2 className="danger-zone-title">{t('admin.users.dangerZone')}</h2>
        </div>
        <div className="danger-zone-item">
          <div>
            <p className="danger-zone-item-title">{t('admin.users.deleteUserTitle')}</p>
            <p className="danger-zone-item-description">{t('admin.users.deleteUserDesc')}</p>
          </div>
          <Button variant="destructive" size="sm" onClick={() => setDeleteUserOpen(true)}>
            {t('admin.users.deleteUser')}
          </Button>
        </div>
      </div>

      <ConfirmDisableDialog
        onOpenChange={setDisableUserOpen}
        open={disableUserOpen}
        title="Disable user?"
        description={`This will disable User #${userId}. They won't be able to log in until re-enabled.`}
        onConfirm={handleDisableUser}
        isLoading={isDisablingUser}
      />
      <ConfirmDeleteDialog
        open={deleteUserOpen}
        onOpenChange={setDeleteUserOpen}
        title="Delete user?"
        description={`This will permanently delete User #${userId} and all their data. This cannot be undone.`}
        onConfirm={handleDeleteUser}
        isLoading={isDeletingUser}
      />
      <ConfirmEnableDialog
        open={enableUserOpen}
        onOpenChange={setEnableUserOpen}
        title="Activate user?"
        description={`This will re-activate User #${userId}. They will be able to log in again.`}
        onConfirm={handleEnableUser}
        isLoading={isEnablingUser}
      />
    </div>
  )
}
