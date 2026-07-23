import { useState, useRef, useEffect } from 'react'
import { useTranslation } from 'react-i18next'
import type { BookShelfEntry } from './types.ts'

interface AddToListMenuProps {
  bookId: number
  onToggle?: (id: string) => void
  onCreateNew?: (name: string) => void
}

export default function AddToListMenu({ bookId, onToggle, onCreateNew }: AddToListMenuProps) {
  const { t } = useTranslation()
  const [open, setOpen] = useState(false)
  const [items, setItems] = useState<BookShelfEntry[]>([])
  const [creating, setCreating] = useState(false)
  const [newName, setNewName] = useState('')
  const ref = useRef<HTMLDivElement>(null)

  useEffect(() => {
    const handler = (e: MouseEvent) => {
      if (ref.current && !ref.current.contains(e.target as Node)) {
        setOpen(false)
        setCreating(false)
        setNewName('')
      }
    }
    document.addEventListener('mousedown', handler)
    return () => document.removeEventListener('mousedown', handler)
  }, [])

  // Load real libraries from DB when menu opens
  useEffect(() => {
    if (!open) return
    fetch(`/auth/me/books/${bookId}/libraries`, { credentials: 'include' })
      .then((r) => r.json())
      .then((data) => setItems(data))
  }, [open, bookId])

  // Toggle ON or OFF depending on current checked state
  const toggle = async (id: string) => {
    const item = items.find((s) => s.id === id)
    if (!item) return

    const method = item.checked ? 'DELETE' : 'POST'
    await fetch(`/auth/me/libraries/${id}/books/${bookId}`, {
      method,
      credentials: 'include',
    })

    setItems((prev) => prev.map((s) => (s.id === id ? { ...s, checked: !s.checked } : s)))
    onToggle?.(id)
  }

  const handleCreate = async () => {
    if (!newName.trim()) return

    // 1. Create the new library
    const libraryRes = await fetch(`/auth/me/libraries`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      credentials: 'include',
      body: JSON.stringify({ name: newName.trim() }),
    })
    if (!libraryRes.ok) return

    const library = await libraryRes.json()

    // 2. Add the book to it immediately
    await fetch(`/auth/me/libraries/${library.id}/books/${bookId}`, {
      method: 'POST',
      credentials: 'include',
    })

    // 3. Update local state
    const newEntry: BookShelfEntry = {
      id: String(library.id),
      label: library.name,
      checked: true,
    }
    setItems((prev) => [...prev, newEntry])
    onCreateNew?.(library.name)
    setNewName('')
    setCreating(false)
  }

  return (
    <div className="relative" ref={ref}>
      {/* Trigger: circle + button */}
      <button
        onClick={() => setOpen((o) => !o)}
        className="w-9 h-9 rounded-full border border-neutral-600 flex items-center justify-center text-white hover:border-neutral-400 hover:bg-neutral-800 transition-colors"
        title={t('book.addToList')}
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          className="w-4 h-4"
          fill="none"
          viewBox="0 0 24 24"
          stroke="currentColor"
          strokeWidth={2}
        >
          <path strokeLinecap="round" strokeLinejoin="round" d="M12 4v16m8-8H4" />
        </svg>
      </button>

      {/* Dropdown */}
      {open && (
        <div className="absolute left-0 top-11 z-50 w-52 bg-[#1e1e1e] border border-neutral-700 rounded-xl shadow-2xl p-3 flex flex-col gap-1">
          {items.map((item) => (
            <button
              key={item.id}
              onClick={() => toggle(item.id)}
              className="flex items-center gap-3 px-2 py-1.5 rounded-lg hover:bg-neutral-800 transition-colors text-left"
            >
              {/* checkbox */}
              <span
                className={`w-4 h-4 flex-shrink-0 border rounded flex items-center justify-center transition-colors ${
                  item.checked ? 'border-white bg-transparent' : 'border-neutral-600 bg-transparent'
                }`}
              >
                {item.checked && (
                  <svg className="w-2.5 h-2.5 text-white" viewBox="0 0 10 10" fill="none">
                    <path
                      d="M1.5 5l2.5 2.5 4.5-4"
                      stroke="currentColor"
                      strokeWidth="1.5"
                      strokeLinecap="round"
                      strokeLinejoin="round"
                    />
                  </svg>
                )}
              </span>
              <span className="text-sm text-neutral-200">{item.label}</span>
            </button>
          ))}

          <div className="border-t border-neutral-700 mt-1 pt-2">
            {creating ? (
              <div className="flex gap-1">
                <input
                  autoFocus
                  value={newName}
                  onChange={(e) => setNewName(e.target.value)}
                  onKeyDown={(e) => {
                    if (e.key === 'Enter') handleCreate()
                    if (e.key === 'Escape') {
                      setCreating(false)
                      setNewName('')
                    }
                  }}
                  placeholder={t('book.listNamePlaceholder')}
                  className="flex-1 bg-neutral-800 border border-neutral-600 rounded-lg px-2 py-1 text-xs text-white placeholder-neutral-500 outline-none focus:border-neutral-400"
                />
                <button
                  onClick={handleCreate}
                  className="px-2 py-1 bg-neutral-700 hover:bg-neutral-600 text-white rounded-lg text-xs transition-colors"
                >
                  ✓
                </button>
              </div>
            ) : (
              <button
                onClick={() => setCreating(true)}
                className="w-full py-1.5 px-2 bg-neutral-800 hover:bg-neutral-700 text-neutral-300 text-sm rounded-lg transition-colors text-center"
              >
                {t('book.createNewList')}
              </button>
            )}
          </div>
        </div>
      )}
    </div>
  )
}
