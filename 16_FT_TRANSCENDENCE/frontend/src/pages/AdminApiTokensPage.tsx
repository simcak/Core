import type { ColumnDef } from '@tanstack/react-table'
import { useCallback, useEffect, useState } from 'react'
import { useTranslation } from 'react-i18next'
import { ArrowUpDown, Copy, KeyRound, Plus, Trash2 } from 'lucide-react'

import { DataTable } from '@/components/common/DataTable.tsx'
import ConfirmDeleteDialog from '@/components/common/ConfirmDeleteDialog.tsx'
import { Button } from '@/components/ui/button.tsx'
import {
  Dialog,
  DialogContent,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog.tsx'
import { Input } from '@/components/ui/input.tsx'
import { Label } from '@/components/ui/label.tsx'
import { ContextMenuItem, ContextMenuSeparator } from '@/components/ui/context-menu.tsx'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { useAuth } from '@/hooks/useAuth.ts'

type PublicApiToken = {
  id: number
  name: string
  created_at: string
  expires_at: string | null
  last_used_at: string | null
  revoked: boolean
}

type CreatedPublicApiToken = PublicApiToken & {
  token: string
}

const formatDate = (value: string | null) => {
  if (!value) return '-'
  return new Intl.DateTimeFormat(undefined, {
    dateStyle: 'medium',
    timeStyle: 'short',
  }).format(new Date(value))
}

export default function AdminApiTokensPage() {
  const { t } = useTranslation()
  const { isAuthorized } = useAuth()
  const apiFetch = useApiFetch()
  const [tokens, setTokens] = useState<PublicApiToken[]>([])
  const [isCreateOpen, setIsCreateOpen] = useState(false)
  const [name, setName] = useState('')
  const [expiresAt, setExpiresAt] = useState('')
  const [createdToken, setCreatedToken] = useState<CreatedPublicApiToken | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<PublicApiToken | null>(null)
  const [isSaving, setIsSaving] = useState(false)
  const [isDeleting, setIsDeleting] = useState(false)
  const [error, setError] = useState<string | null>(null)

  const fetchTokens = useCallback(() => {
    apiFetch('/auth/admin/public-api-keys')
      .then((response) => {
        if (!response.ok) throw new Error(`HTTP: ${response.status}`)
        return response.json()
      })
      .then((data) => setTokens(data))
      .catch((err) => {
        console.error('Failed to load API tokens', err)
        setError(t('admin.apiTokens.loadError'))
      })
  }, [apiFetch, t])

  useEffect(() => {
    fetchTokens()
  }, [fetchTokens])

  if (!isAuthorized('admin')) {
    return <p className="p-5 text-sm text-muted-foreground">{t('admin.accessDenied')}</p>
  }

  const resetCreateForm = () => {
    setName('')
    setExpiresAt('')
    setError(null)
  }

  const handleCreate = async () => {
    if (!name.trim()) {
      setError(t('admin.apiTokens.nameRequired'))
      return
    }
    setIsSaving(true)
    setError(null)
    try {
      const response = await apiFetch('/auth/admin/public-api-keys', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          name,
          expires_at: expiresAt ? new Date(expiresAt).toISOString() : null,
        }),
      })
      if (!response.ok) throw new Error(`Create failed: ${response.status}`)
      const data = await response.json()
      setCreatedToken(data)
      setIsCreateOpen(false)
      resetCreateForm()
      fetchTokens()
    } catch (err) {
      console.error(err)
      setError(t('admin.apiTokens.createError'))
    } finally {
      setIsSaving(false)
    }
  }

  const handleRevoke = async (token: PublicApiToken) => {
    try {
      const response = await apiFetch(`/auth/admin/public-api-keys/${token.id}/revoke`, {
        method: 'PATCH',
      })
      if (!response.ok) throw new Error(`Revoke failed: ${response.status}`)
      fetchTokens()
    } catch (err) {
      console.error(err)
      setError(t('admin.apiTokens.revokeError'))
    }
  }

  const handleDelete = async () => {
    if (!deleteTarget) return
    setIsDeleting(true)
    try {
      const response = await apiFetch(`/auth/admin/public-api-keys/${deleteTarget.id}`, {
        method: 'DELETE',
      })
      if (!response.ok) throw new Error(`Delete failed: ${response.status}`)
      setDeleteTarget(null)
      fetchTokens()
    } catch (err) {
      console.error(err)
      setError(t('admin.apiTokens.deleteError'))
    } finally {
      setIsDeleting(false)
    }
  }

  const columns: ColumnDef<PublicApiToken>[] = [
    {
      id: 'id',
      accessorKey: 'id',
      header: ({ column }) => (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          {t('admin.apiTokens.id')}
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      ),
      cell: ({ row }) => (
        <span className="font-mono text-xs text-muted-foreground">{row.original.id}</span>
      ),
    },
    {
      id: 'name',
      accessorKey: 'name',
      header: ({ column }) => (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          {t('admin.apiTokens.name')}
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      ),
    },
    {
      id: 'created_at',
      accessorKey: 'created_at',
      header: t('admin.apiTokens.created'),
      cell: ({ row }) => formatDate(row.original.created_at),
    },
    {
      id: 'expires_at',
      accessorKey: 'expires_at',
      header: t('admin.apiTokens.expires'),
      cell: ({ row }) => formatDate(row.original.expires_at),
    },
    {
      id: 'status',
      accessorFn: (row) =>
        row.revoked ? t('admin.apiTokens.revoked') : t('admin.apiTokens.active'),
      header: t('admin.apiTokens.status'),
      cell: ({ row }) => (
        <span
          className={
            row.original.revoked
              ? 'text-xs font-medium text-muted-foreground'
              : 'text-xs font-medium text-emerald-400'
          }
        >
          {row.original.revoked ? t('admin.apiTokens.revoked') : t('admin.apiTokens.active')}
        </span>
      ),
    },
    {
      id: 'actions',
      header: t('admin.apiTokens.actions'),
      cell: ({ row }) => (
        <div className="flex items-center gap-2">
          <Button
            variant="outline"
            size="sm"
            disabled={row.original.revoked}
            onClick={(event) => {
              event.stopPropagation()
              handleRevoke(row.original)
            }}
          >
            {t('admin.apiTokens.revoke')}
          </Button>
          <Button
            variant="destructive"
            size="sm"
            onClick={(event) => {
              event.stopPropagation()
              setDeleteTarget(row.original)
            }}
          >
            <Trash2 className="h-4 w-4" />
          </Button>
        </div>
      ),
    },
  ]

  return (
    <div>
      <div className="flex items-center justify-between gap-4">
        <div>
          <h1 className="text-2xl font-bold tracking-tight">{t('admin.apiTokens.title')}</h1>
          <p className="text-sm text-muted-foreground mt-1">
            {t('admin.apiTokens.showing', { count: tokens.length })}
          </p>
        </div>
        <Button size="sm" onClick={() => setIsCreateOpen(true)}>
          <Plus className="mr-2 h-4 w-4" />
          {t('admin.apiTokens.create')}
        </Button>
      </div>

      {error && <p className="mt-4 text-sm text-destructive">{error}</p>}

      <DataTable
        columns={columns}
        data={tokens}
        filterColumns={['name', 'status']}
        filterPlaceholder={t('admin.apiTokens.searchPlaceholder')}
        renderContextMenu={(token) => (
          <>
            <ContextMenuItem onClick={() => navigator.clipboard.writeText(token.name)}>
              {t('admin.apiTokens.copyName')}
            </ContextMenuItem>
            <ContextMenuItem disabled={token.revoked} onClick={() => handleRevoke(token)}>
              {t('admin.apiTokens.revoke')}
            </ContextMenuItem>
            <ContextMenuSeparator />
            <ContextMenuItem
              className="text-destructive focus:text-destructive"
              onClick={() => setDeleteTarget(token)}
            >
              {t('admin.apiTokens.delete')}
            </ContextMenuItem>
          </>
        )}
      />

      <Dialog
        open={isCreateOpen}
        onOpenChange={(open) => {
          setIsCreateOpen(open)
          if (!open) resetCreateForm()
        }}
      >
        <DialogContent className="sm:max-w-md">
          <DialogHeader>
            <DialogTitle>{t('admin.apiTokens.createTitle')}</DialogTitle>
          </DialogHeader>
          <div className="space-y-4">
            <div className="space-y-2">
              <Label htmlFor="api-token-name">{t('admin.apiTokens.name')}</Label>
              <Input
                id="api-token-name"
                value={name}
                onChange={(event) => setName(event.target.value)}
                autoFocus
              />
            </div>
            <div className="space-y-2">
              <Label htmlFor="api-token-expires">{t('admin.apiTokens.expires')}</Label>
              <Input
                id="api-token-expires"
                type="datetime-local"
                value={expiresAt}
                onChange={(event) => setExpiresAt(event.target.value)}
              />
            </div>
          </div>
          <DialogFooter>
            <Button variant="outline" onClick={() => setIsCreateOpen(false)} disabled={isSaving}>
              {t('common.cancel')}
            </Button>
            <Button onClick={handleCreate} disabled={isSaving}>
              <KeyRound className="mr-2 h-4 w-4" />
              {isSaving ? t('admin.apiTokens.creating') : t('admin.apiTokens.create')}
            </Button>
          </DialogFooter>
        </DialogContent>
      </Dialog>

      <Dialog open={!!createdToken} onOpenChange={(open) => !open && setCreatedToken(null)}>
        <DialogContent className="sm:max-w-xl">
          <DialogHeader>
            <DialogTitle>{t('admin.apiTokens.createdTitle')}</DialogTitle>
          </DialogHeader>
          <div className="space-y-3">
            <p className="text-sm text-muted-foreground">{t('admin.apiTokens.createdDesc')}</p>
            <div className="flex items-center gap-2 rounded-md border bg-muted/40 p-2">
              <code className="min-w-0 flex-1 break-all text-xs">{createdToken?.token}</code>
              <Button
                variant="outline"
                size="sm"
                onClick={() => {
                  if (createdToken?.token) navigator.clipboard.writeText(createdToken.token)
                }}
              >
                <Copy className="h-4 w-4" />
              </Button>
            </div>
          </div>
          <DialogFooter>
            <Button onClick={() => setCreatedToken(null)}>{t('admin.apiTokens.done')}</Button>
          </DialogFooter>
        </DialogContent>
      </Dialog>

      <ConfirmDeleteDialog
        open={!!deleteTarget}
        onOpenChange={(open) => {
          if (!open) setDeleteTarget(null)
        }}
        title={t('admin.apiTokens.deleteTitle')}
        description={t('admin.apiTokens.deleteDesc', { name: deleteTarget?.name ?? '' })}
        onConfirm={handleDelete}
        isLoading={isDeleting}
      />
    </div>
  )
}
