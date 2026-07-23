import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { Button } from '@/components/ui/button.tsx'
import { Input } from '@/components/ui/input.tsx'
import { Label } from '@/components/ui/label.tsx'

type FormState = {
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
}

export default function AdminUserFormPage() {
  const { t } = useTranslation()
  const setField = (field: keyof FormState, value: string | null) =>
    setForm((prev) => ({ ...prev, [field]: value }))

  const navigate = useNavigate()
  const apiFetch = useApiFetch()

  const [form, setForm] = useState<FormState>({
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
  })

  const [isSubmitting, setIsSubmitting] = useState(false)
  const [error, setError] = useState<string | null>(null)
  const [roles, setRoles] = useState<{ id: number; role_name: string }[]>([])

  useEffect(() => {
    apiFetch('/auth/roles')
      .then((r) => r.json())
      .then((data: { id: number; role_name: string }[]) => {
        setRoles(data)
        const userRole = data.find((r) => r.role_name.toLowerCase() === 'user')
        if (userRole) setForm((prev) => ({ ...prev, role_id: userRole.id }))
      })
  }, [apiFetch])

  const handleSubmit = async () => {
    if (!form.username || !form.email) {
      setError(t('admin.users.usernameRequired'))
      return
    }
    setIsSubmitting(true)
    setError(null)
    try {
      const UserRes = await apiFetch('/auth/admin/users', {
        method: 'POST',
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
      <div>
        <h1 className="text-2xl font-bold tracking-tight">{t('admin.users.newUser')}</h1>
        <p className="text-sm text-muted-foreground mt-1">{t('admin.users.newUserDesc')}</p>
      </div>

      {error && <p className="text-sm text-destructive">{error}</p>}

      <div className="grid grid-cols-2 gap-4">
        <div className="col-span-2 flex flex-col gap-1.5">
          <Label>
            {t('admin.users.username')} <span className="text-destructive">*</span>
          </Label>
          <Input value={form.username} onChange={(e) => setField('username', e.target.value)} />
        </div>

        <div className="col-span-2 flex flex-col gap-1.5">
          <Label>
            {t('admin.users.email')} <span className="text-destructive">*</span>
          </Label>
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

      <div className="flex gap-3">
        <Button variant="outline" onClick={() => navigate('/admin/')} disabled={isSubmitting}>
          {t('admin.users.cancel')}
        </Button>
        <Button onClick={handleSubmit} disabled={isSubmitting}>
          {isSubmitting ? t('admin.users.creating') : t('admin.users.createUser')}
        </Button>
      </div>
    </div>
  )
}
