import { useRef, useEffect } from 'react'
import { useTranslation } from 'react-i18next'
import type { ShelfFolder } from './types'

interface FolderTabsProps {
  folders: ShelfFolder[]
  activeFolderId: string | null
  renamingId: string | null
  renameVal: string
  onSelect: (id: string | null) => void
  onContextMenu: (e: React.MouseEvent, folderId: string) => void
  onRenameChange: (val: string) => void
  onRenameCommit: (id: string) => void
  onRenameCancel: () => void
}

export default function FolderTabs({
  folders,
  activeFolderId,
  renamingId,
  renameVal,
  onSelect,
  onContextMenu,
  onRenameChange,
  onRenameCommit,
  onRenameCancel,
}: FolderTabsProps) {
  const { t } = useTranslation()
  const renameRef = useRef<HTMLInputElement>(null)

  useEffect(() => {
    if (renamingId) renameRef.current?.focus()
  }, [renamingId])

  return (
    <div style={{ display: 'flex', flexWrap: 'wrap', gap: 12 }}>
      {/* All tab */}
      <button
        onClick={() => onSelect(null)}
        style={{
          padding: '10px 22px',
          borderRadius: 12,
          border: '2px solid rgba(255,255,255,0.35)',
          background: !activeFolderId ? 'rgba(255,255,255,0.08)' : 'transparent',
          color: !activeFolderId ? 'rgba(255,255,255,0.9)' : 'rgba(255,255,255,0.4)',
          fontWeight: 500,
          fontSize: 15,
          cursor: 'pointer',
          transition: 'all 0.18s',
          whiteSpace: 'nowrap',
        }}
      >
        {t('shelf.all')}
      </button>

      {/* Folder tabs */}
      {folders.map((folder) => {
        const isActive = folder.id === activeFolderId
        return (
          <button
            key={folder.id}
            onContextMenu={(e) => onContextMenu(e, folder.id)}
            onClick={() => onSelect(folder.id)}
            style={{
              position: 'relative',
              padding: '10px 22px',
              borderRadius: 12,
              border: `2px solid ${folder.color}`,
              background: isActive ? `${folder.color}18` : 'transparent',
              color: isActive ? folder.color : `${folder.color}bb`,
              fontWeight: 500,
              fontSize: 15,
              cursor: 'pointer',
              transition: 'all 0.18s',
              whiteSpace: 'nowrap',
            }}
            onMouseEnter={(e) => {
              if (!isActive) {
                ;(e.currentTarget as HTMLElement).style.background = `${folder.color}12`
                ;(e.currentTarget as HTMLElement).style.color = folder.color
              }
            }}
            onMouseLeave={(e) => {
              if (!isActive) {
                ;(e.currentTarget as HTMLElement).style.background = 'transparent'
                ;(e.currentTarget as HTMLElement).style.color = `${folder.color}bb`
              }
            }}
          >
            {renamingId === folder.id ? (
              <input
                ref={renameRef}
                value={renameVal}
                onChange={(e) => onRenameChange(e.target.value)}
                onBlur={() => onRenameCommit(folder.id)}
                onKeyDown={(e) => {
                  if (e.key === 'Enter') onRenameCommit(folder.id)
                  if (e.key === 'Escape') onRenameCancel()
                }}
                onClick={(e) => e.stopPropagation()}
                style={{
                  background: 'transparent',
                  border: 'none',
                  outline: 'none',
                  color: 'inherit',
                  fontWeight: 'inherit',
                  fontSize: 'inherit',
                  width: Math.max(60, renameVal.length * 9),
                }}
              />
            ) : (
              folder.label
            )}
          </button>
        )
      })}
    </div>
  )
}
