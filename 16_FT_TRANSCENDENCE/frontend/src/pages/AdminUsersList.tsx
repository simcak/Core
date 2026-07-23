import type { ColumnDef } from '@tanstack/react-table'
import { useState, useEffect } from 'react'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { useAuth } from '../hooks/useAuth'
import { useNavigate } from 'react-router-dom'
import { ArrowUpDown } from 'lucide-react'
import { DataTable } from '@/components/common/DataTable.tsx'
import { Button } from '@/components/ui/button.tsx'
//import { ConfirmDeleteDialog } from '@/components/common/ConfirmDeleteDialog.tsx'

{
  /*
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu'
*/
}
import { ContextMenuItem, ContextMenuSeparator } from '@/components/ui/context-menu.tsx'

// ── Types ────────────────────────────────────────────────────────────────────

type Role = {
  id: number
  role_name: string
  created_at?: string
  updated_at?: string
}

type UserForAdmin = {
  id: number
  username: string
  email: string
  first_name: string | null
  last_name: string | null
  phone: string | null
  role_id: number
  role: Role
  created_at: string
  updated_at: string
  last_login_at: string | null
  //  name: string
  status: string
}

{
  /*
type UserFormData = {
  username: string
  email: string
  first_name: string
  last_name: string
  phone: string
  role_id: number
}

const EMPTY_FORM: UserFormData = {
  username: '',
  email: '',
  first_name: '',
  last_name: '',
  phone: '',
  role_id: 2,
}

const ROLES = [
  { value: 1, label: 'Admin' },
  { value: 2, label: 'User' },
  { value: 3, label: 'Author' },
  { value: 4, label: 'Guest' },
]
*/
}

export default function AdminUsersList() {
  const { t } = useTranslation()
  const { isAuthorized } = useAuth()
  const [users, setUsers] = useState<UserForAdmin[]>([])
  //  const [editTarget, setEditTarget] = useState<UserForAdmin | null | 'new'>(null)
  //  const [formData, setFormData] = useState<UserFormData>(EMPTY_FORM)
  //  const [isSaving, setIsSaving] = useState(false)
  //  const [deleteTarget, setDeleteTarget] = useState<UserForAdmin | null>(null)
  //  const [isDeleting, setIsDeleting] = useState(false)

  const apiFetch = useApiFetch()
  const navigate = useNavigate()

  // ── Fetch users ────────────────────────────────────────────────────────────

  useEffect(() => {
    let cancelled = false
    apiFetch(`/auth/admin/users`)
      .then((response) => {
        if (!response.ok) throw new Error(`HTTP: ${response.status}`)
        return response.json()
      })
      .then((data) => {
        if (!cancelled) setUsers(data)
      })
      .catch((err) => console.error('Failed to load users', err))
    return () => {
      cancelled = true
    }
  }, [apiFetch])

  // ── Auth guard ─────────────────────────────────────────────────────────────

  if (!isAuthorized('admin')) {
    return <p className="p-5 text-sm text-muted-foreground">{t('admin.accessDenied')}</p>
  }

  {
    /*
  const handleDelete = async () => {
    if (!deleteTarget) return
    setIsDeleting(true)
    try {
      const res = await apiFetch(`/api/books/${deleteTarget.id}`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Delete failed: ${res.status}`)
      setDeleteTarget(null)
      fetchUsers()
    } catch (e) {
      console.error(e)
    } finally {
      setIsDeleting(false)
    }
  }
*/
  }

  const columns: ColumnDef<UserForAdmin>[] = [
    {
      id: 'id',
      accessorKey: 'id',
      header: ({ column }) => (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          {t('admin.users.id')}
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      ),
      cell: ({ row }) => (
        <span className="font-mono text-xs text-muted-foreground">{row.original.id}</span>
      ),
    },
    {
      id: 'username',
      accessorKey: 'username',
      header: ({ column }) => (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          {t('admin.users.username')}
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      ),
      cell: ({ row }) => (
        <span className="font-mono text-xs text-muted-foreground">{row.original.username}</span>
      ),
    },
    {
      id: 'email',
      accessorKey: 'email',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.users.email')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
    },
    {
      id: 'first_name',
      accessorFn: (row) => {
        return `${row.first_name ?? ''} ${row.last_name ?? ''}`.trim() || '-'
      },
      header: ({ column }) => (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          {t('admin.users.name')}
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      ),
    },
    {
      id: 'phone',
      accessorKey: 'phone',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.users.phone')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
      cell: ({ getValue }) => {
        const phone = getValue<string>()
        return phone || '-'
      },
    },
    {
      id: 'role',
      accessorKey: 'role.role_name',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.users.role')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
      cell: ({ getValue }) => {
        const role = getValue<string>()
        return role.charAt(0).toUpperCase() + role.slice(1)
      },
    },
    {
      id: 'status',
      accessorKey: 'status',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.users.status')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
    },
  ]
  return (
    <div>
      <div className="flex items-center justify-between">
        <div>
          <h1 className="text-2xl font-bold tracking-tight">{t('admin.users.title')}</h1>
          <p className="text-sm text-muted-foreground mt-1">
            {t('admin.users.showing', { count: users.length })}
          </p>
        </div>
        <Button size="sm" onClick={() => navigate('/admin/users/new')}>
          {t('admin.users.addUser')}
        </Button>
      </div>
      <DataTable
        columns={columns}
        data={users}
        filterColumns={['username', 'username']}
        filterPlaceholder={t('admin.users.searchPlaceholder')}
        onRowClick={(user) => navigate(`/admin/users/${user.id}`)}
        renderContextMenu={(user) => (
          <>
            <ContextMenuItem onClick={() => navigate(`/admin/users/${user.id}`)}>
              {t('admin.users.manageUser')}
            </ContextMenuItem>
            <ContextMenuItem onClick={() => navigator.clipboard.writeText(user.username)}>
              {t('admin.users.copyUsername')}
            </ContextMenuItem>
            <ContextMenuSeparator />
          </>
        )}
      />
      {/*
      <ConfirmDeleteDialog
        open={!!deleteTarget}
        onOpenChange={(open) => {
          if (!open) setDeleteTarget(null)
        }}
        title="Delete book?"
        description={`This will permanently delete "${deleteTarget?.translations[0]?.title ?? `Book #${deleteTarget?.id}`}" and all its audio files.`}
        onConfirm={handleDelete}
        isLoading={isDeleting}
      />
*/}
    </div>
  )
}
