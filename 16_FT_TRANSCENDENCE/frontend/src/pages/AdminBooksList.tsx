import type { ColumnDef } from '@tanstack/react-table'
import { useCallback, useEffect, useState } from 'react'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { DataTable } from '@/components/common/DataTable.tsx'
import { Link, useNavigate } from 'react-router-dom'
import { Button } from '@/components/ui/button.tsx'
import { ArrowUpDown } from 'lucide-react'
import ConfirmDeleteDialog from '@/components/common/ConfirmDeleteDialog.tsx'

import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu'
import { ContextMenuItem, ContextMenuSeparator } from '@/components/ui/context-menu.tsx'

type Author = {
  id: number
  author_name: string
}

type Translation = {
  lang: string
  title: string
  description: string | null
  cover_image_filename: string | null
  sample_url: string | null
}

type BookShort = {
  id: number
  author: Author
  translations: Translation[]
  price: number
  currency: string
  language_code: string | null
  product_status: string
}

const STATUS_OPTIONS = ['draft', 'active', 'archived', 'deleted'] as const
type Status = (typeof STATUS_OPTIONS)[number]

const STATUS_BADGE: Record<string, string> = {
  active: 'bg-green-100 text-green-800 dark:bg-green-900/30 dark:text-green-400',
  draft: 'bg-yellow-100 text-yellow-800 dark:bg-yellow-900/30 dark:text-yellow-400',
  archived: 'bg-muted text-muted-foreground',
  deleted: 'bg-red-100 text-red-800 dark:bg-red-900/30 dark:text-red-400',
}

export default function AdminBooksList() {
  const { t } = useTranslation()
  const [books, setBooks] = useState<BookShort[]>([])
  const [selectedLangs, setSelectedLangs] = useState<Record<number, string>>({})
  const [statusFilter, setStatusFilter] = useState<Status | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<BookShort | null>(null)
  const [isDeleting, setIsDeleting] = useState(false)
  const [selectedIds, setSelectedIds] = useState<Set<number>>(new Set())
  const [bulkStatus, setBulkStatus] = useState<Status>('active')
  const [isBulkUpdating, setIsBulkUpdating] = useState(false)
  const apiFetch = useApiFetch()
  const navigate = useNavigate()

  const fetchBooks = useCallback(() => {
    apiFetch(`/api/books`)
      .then((response) => {
        if (!response.ok) throw new Error(`HTTP: ${response.status}`)
        return response.json()
      })
      .then((data) => setBooks(data))
  }, [apiFetch])

  useEffect(() => {
    fetchBooks()
  }, [fetchBooks])

  const toggleSelect = (id: number, e: React.MouseEvent | React.ChangeEvent) => {
    e.stopPropagation()
    setSelectedIds((prev) => {
      const next = new Set(prev)
      if (next.has(id)) {
        next.delete(id)
      } else {
        next.add(id)
      }
      return next
    })
  }

  const handleBulkUpdate = async () => {
    if (!selectedIds.size) return
    setIsBulkUpdating(true)
    try {
      await Promise.all(
        [...selectedIds].map((id) =>
          apiFetch(`/api/books/${id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ product_status: bulkStatus }),
          })
        )
      )
      setSelectedIds(new Set())
      fetchBooks()
    } catch (e) {
      console.error(e)
    } finally {
      setIsBulkUpdating(false)
    }
  }

  const handleDelete = async () => {
    if (!deleteTarget) return
    setIsDeleting(true)
    try {
      const res = await apiFetch(`/api/books/${deleteTarget.id}`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Delete failed: ${res.status}`)
      setDeleteTarget(null)
      fetchBooks()
    } catch (e) {
      console.error(e)
    } finally {
      setIsDeleting(false)
    }
  }

  const statusCount = (status: Status) => books.filter((b) => b.product_status === status).length

  const filteredBooks = statusFilter
    ? books.filter((b) => b.product_status === statusFilter)
    : books

  const allVisibleSelected =
    filteredBooks.length > 0 && filteredBooks.every((b) => selectedIds.has(b.id))
  const someVisibleSelected = filteredBooks.some((b) => selectedIds.has(b.id))

  const toggleSelectAll = () => {
    if (allVisibleSelected) {
      setSelectedIds((prev) => {
        const next = new Set(prev)
        filteredBooks.forEach((b) => next.delete(b.id))
        return next
      })
    } else {
      setSelectedIds((prev) => {
        const next = new Set(prev)
        filteredBooks.forEach((b) => next.add(b.id))
        return next
      })
    }
  }

  const columns: ColumnDef<BookShort>[] = [
    {
      id: 'select',
      header: () => (
        <input
          type="checkbox"
          className="h-4 w-4 cursor-pointer"
          checked={allVisibleSelected}
          ref={(el) => {
            if (el) el.indeterminate = someVisibleSelected && !allVisibleSelected
          }}
          onChange={toggleSelectAll}
          onClick={(e) => e.stopPropagation()}
        />
      ),
      cell: ({ row }) => (
        <input
          type="checkbox"
          className="h-4 w-4 cursor-pointer"
          checked={selectedIds.has(row.original.id)}
          onChange={(e) => toggleSelect(row.original.id, e)}
          onClick={(e) => e.stopPropagation()}
        />
      ),
    },
    { accessorKey: 'id', header: t('admin.books.id') },
    {
      id: 'author_name',
      accessorKey: 'author.author_name',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.books.author')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
      cell: ({ row }) => {
        const author = row.original.author
        return (
          <Link
            to={`/author/${author.id}`}
            className="hover:text-orange-400 hover:underline"
            onClick={(event) => event.stopPropagation()}
          >
            {author.author_name}
          </Link>
        )
      },
    },
    {
      id: 'title',
      accessorKey: 'title',
      accessorFn: (row) => row.translations[0]?.title ?? '-',
      header: ({ column }) => {
        return (
          <Button
            variant="ghost"
            onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
          >
            {t('admin.books.title')}
            <ArrowUpDown className="ml-2 h-4 w-4" />
          </Button>
        )
      },
      cell: ({ row }) => {
        const book = row.original
        const activeLang = selectedLangs[book.id] ?? book.translations[0]?.lang ?? ''
        const translation =
          book.translations.find((t) => t.lang === activeLang) ?? book.translations[0]
        return <span>{translation?.title ?? '—'}</span>
      },
    },
    {
      id: 'lang',
      header: t('admin.books.lang'),
      cell: ({ row }) => {
        const book = row.original
        const activeLang = selectedLangs[book.id] ?? book.translations[0]?.lang ?? ''
        if (book.translations.length <= 1) {
          return (
            <span className="text-xs text-muted-foreground font-mono">
              {activeLang.toUpperCase()}
            </span>
          )
        }
        return (
          <DropdownMenu>
            <DropdownMenuTrigger asChild>
              <Button
                variant="outline"
                size="sm"
                className="h-7 text-xs font-mono"
                onClick={(e) => e.stopPropagation()}
              >
                {activeLang.toUpperCase()}
              </Button>
            </DropdownMenuTrigger>
            <DropdownMenuContent align="start">
              {book.translations.map((t) => (
                <DropdownMenuItem
                  key={t.lang}
                  onClick={() => setSelectedLangs((prev) => ({ ...prev, [book.id]: t.lang }))}
                  className={activeLang === t.lang ? 'bg-accent' : ''}
                >
                  {t.lang.toUpperCase()}
                </DropdownMenuItem>
              ))}
            </DropdownMenuContent>
          </DropdownMenu>
        )
      },
    },
    {
      id: 'product_status',
      accessorKey: 'product_status',
      header: t('admin.books.statusLabel'),
      cell: ({ row }) => {
        const status = row.original.product_status
        return (
          <span
            className={`inline-flex items-center rounded-full px-2 py-0.5 text-xs font-medium ${STATUS_BADGE[status] ?? STATUS_BADGE.archived}`}
          >
            {t(`admin.books.${status}`, { defaultValue: status })}
          </span>
        )
      },
    },
  ]

  return (
    <div className="flex flex-col gap-4">
      <div className="flex items-center justify-between">
        <div>
          <h1 className="text-2xl font-bold tracking-tight">{t('admin.books.pageTitle')}</h1>
          <p className="text-sm text-muted-foreground mt-1">
            {t('admin.books.showing', { count: filteredBooks.length })}
          </p>
        </div>
        <Button size="sm" onClick={() => navigate('/admin/books/new')}>
          {t('admin.books.addBook')}
        </Button>
      </div>

      <div className="flex items-center gap-1 flex-wrap">
        <button
          onClick={() => setStatusFilter(null)}
          className={`rounded-md px-3 py-1.5 text-sm font-medium transition-colors ${
            statusFilter === null
              ? 'bg-foreground text-background'
              : 'bg-muted text-muted-foreground hover:bg-muted/80'
          }`}
        >
          {t('admin.books.statusAll')}
          <span className="ml-1.5 tabular-nums opacity-60">{books.length}</span>
        </button>
        {STATUS_OPTIONS.map((s) => (
          <button
            key={s}
            onClick={() => setStatusFilter(statusFilter === s ? null : s)}
            className={`rounded-md px-3 py-1.5 text-sm font-medium transition-colors ${
              statusFilter === s
                ? 'bg-foreground text-background'
                : 'bg-muted text-muted-foreground hover:bg-muted/80'
            }`}
          >
            {t(`admin.books.${s}`, { defaultValue: s })}
            <span className="ml-1.5 tabular-nums opacity-60">{statusCount(s)}</span>
          </button>
        ))}
      </div>

      {selectedIds.size > 0 && (
        <div className="flex items-center gap-3 rounded-lg border bg-muted/50 px-4 py-2.5">
          <span className="text-sm font-medium">
            {t('admin.books.nSelected', { count: selectedIds.size })}
          </span>
          <div className="h-4 w-px bg-border" />
          <span className="text-sm text-muted-foreground">{t('admin.books.setStatus')}</span>
          <select
            value={bulkStatus}
            onChange={(e) => setBulkStatus(e.target.value as Status)}
            className="border rounded px-2 py-1 text-sm bg-background"
          >
            {STATUS_OPTIONS.map((s) => (
              <option key={s} value={s}>
                {t(`admin.books.${s}`, { defaultValue: s })}
              </option>
            ))}
          </select>
          <Button size="sm" onClick={handleBulkUpdate} disabled={isBulkUpdating}>
            {isBulkUpdating ? t('admin.books.updating') : t('admin.books.apply')}
          </Button>
          <Button
            size="sm"
            variant="ghost"
            onClick={() => setSelectedIds(new Set())}
            disabled={isBulkUpdating}
          >
            {t('admin.books.clearSelection')}
          </Button>
        </div>
      )}

      <DataTable
        columns={columns}
        data={filteredBooks}
        filterColumns={['title', 'author_name']}
        filterPlaceholder={t('admin.books.searchPlaceholder')}
        onRowClick={(book) => navigate(`/admin/books/${book.id}`)}
        rowClassName={(book) => (book.product_status === 'deleted' ? 'opacity-40' : undefined)}
        renderContextMenu={(book) => (
          <>
            <ContextMenuItem onClick={() => navigate(`/admin/books/${book.id}`)}>
              {t('admin.books.manageBook')}
            </ContextMenuItem>
            <ContextMenuItem
              onClick={() => navigator.clipboard.writeText(book.translations[0]?.title ?? '')}
            >
              {t('admin.books.copyTitle')}
            </ContextMenuItem>
            <ContextMenuSeparator />
            <ContextMenuItem
              className="text-destructive focus:text-destructive"
              onClick={() => setDeleteTarget(book)}
            >
              {t('admin.books.delete')}
            </ContextMenuItem>
          </>
        )}
      />
      <ConfirmDeleteDialog
        open={!!deleteTarget}
        onOpenChange={(open) => {
          if (!open) setDeleteTarget(null)
        }}
        title="Mark book as deleted?"
        description={`"${deleteTarget?.translations[0]?.title ?? `Book #${deleteTarget?.id}`}" will be marked as deleted and hidden from users.`}
        onConfirm={handleDelete}
        isLoading={isDeleting}
      />
    </div>
  )
}
