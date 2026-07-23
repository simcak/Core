import { useState, useCallback, useEffect } from 'react'
import { useSearchParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import type { ShortBook } from '../components/book/types'
import { PALETTE } from '../components/shelf/types'
import type { ShelfFolder } from '../components/shelf/types'
import FolderTabs from '../components/shelf/ShelfFolderSection'
import FolderContextMenu from '../components/shelf/FolderContextMenu'
import type { CtxMenu } from '../components/shelf/FolderContextMenu'
import ShelfBooksSection from '../components/shelf/ShelfBooksSection'
 
const API_URL = import.meta.env.VITE_API_URL ?? '/api'
 
export default function ShelfPage() {
  const { t } = useTranslation()
  const [searchParams, setSearchParams] = useSearchParams()
 
  const [allBooks, setAllBooks] = useState<ShortBook[]>([])
  const [loading, setLoading] = useState(true)
 
  const [folders, setFolders] = useState<ShelfFolder[]>([])
  const [ctx, setCtx] = useState<CtxMenu | null>(null)
  const [showColorFor, setShowColorFor] = useState<string | null>(null)
  const [renamingId, setRenamingId] = useState<string | null>(null)
  const [renameVal, setRenameVal] = useState('')
 
  // Active folder driven by ?f=<id>; null = all books
  const activeFolderId = searchParams.get('f')
  const activeFolder = folders.find((f) => f.id === activeFolderId) ?? null


  // ── Fetch full book library ───────────────────────────────────────────────
  useEffect(() => {
    const controller = new AbortController()
    fetch(`${API_URL}/books`, { signal: controller.signal })
      .then((r) => (r.ok ? r.json() : []))
      .then((data: ShortBook[]) => {
        setAllBooks(data)
        setLoading(false)
      })
      .catch(() => setLoading(false))
    return () => controller.abort()
  }, [])

  // ── Fetch folders from DB ────────────────────────────────────────────────
  useEffect(() => {
    const controller = new AbortController()
    fetch(`${API_URL}/auth/me/libraries`, {
      signal: controller.signal,
      credentials: 'include',
    })
      .then((r) => (r.ok ? r.json() : []))
      .then((data: { id: number; name: string; book_ids: number[] }[]) => {
        setFolders(
          data.map((lib, i) => ({
            id:      String(lib.id),
            label:   lib.name,
            color:   PALETTE[i % PALETTE.length],
            bookIds: lib.book_ids,
          }))
        )
      })
      .catch(() => {})
    return () => controller.abort()
  }, [])

  const books: ShortBook[] = activeFolder
    ? allBooks.filter((b) => activeFolder.bookIds.includes(b.id))
    : allBooks

  // ── Navigation ────────────────────────────────────────────────────────────
  const selectFolder = useCallback(
    (id: string | null) => {
      if (id === null) {
        setSearchParams({})
      } else {
        setSearchParams({ f: id })
      }
    },
    [setSearchParams]
  )

  // ── Context menu handlers ─────────────────────────────────────────────────
  const openCtx = useCallback((e: React.MouseEvent, folderId: string) => {
    e.preventDefault()
    setCtx({ folderId, x: e.clientX, y: e.clientY })
    setShowColorFor(null)
  }, [])

  const closeCtx = useCallback(() => {
    setCtx(null)
    setShowColorFor(null)
  }, [])

  const handlePickColor = (folderId: string, color: string) => {
    setFolders((f) => f.map((x) => (x.id === folderId ? { ...x, color } : x)))
    closeCtx()
  }

  const handleRename = (folderId: string, label: string) => {
    setRenamingId(folderId)
    setRenameVal(label)
    closeCtx()
  }

  const handleRenameCommit = (id: string) => {
    const trimmed = renameVal.trim()
    if (!trimmed) { setRenamingId(null); return }

    setFolders((f) => f.map((x) => (x.id === id ? { ...x, label: trimmed } : x)))
    setRenamingId(null)

    fetch(`${API_URL}/auth/me/libraries/${id}`, {
      method: 'PATCH',
      credentials: 'include',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ name: trimmed }),
    })
  }

  const handleRemove = (id: string) => {
  setFolders((f) => f.filter((x) => x.id !== id))
    if (activeFolderId === id) selectFolder(null)
    closeCtx()

    fetch(`${API_URL}/auth/me/libraries/${id}`, {
      method: 'DELETE',
      credentials: 'include',
    })
  }

  return (
    <div className="flex flex-col gap-8 max-w-5xl mx-auto">
      <h1
        style={{
          fontSize: 28,
          fontWeight: 700,
          color: 'rgba(255,255,255,0.92)',
          letterSpacing: '-0.5px',
        }}
      >
        {t('shelf.title')}
      </h1>
      <FolderTabs
        folders={folders}
        activeFolderId={activeFolderId}
        renamingId={renamingId}
        renameVal={renameVal}
        onSelect={selectFolder}
        onContextMenu={openCtx}
        onRenameChange={setRenameVal}
        onRenameCommit={handleRenameCommit}
        onRenameCancel={() => setRenamingId(null)}
      />

      {ctx && (
        <FolderContextMenu
          ctx={ctx}
          folders={folders}
          showColorFor={showColorFor}
          onClose={closeCtx}
          onShowColor={setShowColorFor}
          onPickColor={handlePickColor}
          onRename={handleRename}
          onRemove={handleRemove}
        />
      )}

      <ShelfBooksSection
        books={books}
        loading={loading}
        accentColor={activeFolder?.color ?? 'rgba(255,255,255,0.45)'}
      />
    </div>
  )
}
