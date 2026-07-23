import { useRef, useEffect } from 'react'
import { useTranslation } from 'react-i18next'
import ColorPicker from './ColorPicker'
import type { ShelfFolder } from './types'

export interface CtxMenu {
  folderId: string
  x: number
  y: number
}

interface FolderContextMenuProps {
  ctx: CtxMenu
  folders: ShelfFolder[]
  showColorFor: string | null
  onClose: () => void
  onShowColor: (folderId: string) => void
  onPickColor: (folderId: string, color: string) => void
  onRename: (folderId: string, label: string) => void
  onRemove: (folderId: string) => void
}

const itemStyle: React.CSSProperties = {
  display: 'block',
  width: '100%',
  textAlign: 'left',
  padding: '8px 16px',
  background: 'transparent',
  color: 'rgba(255,255,255,0.85)',
  fontSize: 14,
  cursor: 'pointer',
  border: 'none',
  transition: 'background 0.15s',
}

/** After right click, show context menu */
export default function FolderContextMenu({
  ctx,
  folders,
  showColorFor,
  onClose,
  onShowColor,
  onPickColor,
  onRename,
  onRemove,
}: FolderContextMenuProps) {
  const { t } = useTranslation()
  const ref = useRef<HTMLDivElement>(null)

  useEffect(() => {
    const handler = (e: MouseEvent) => {
      if (ref.current && !ref.current.contains(e.target as Node)) onClose()
    }
    document.addEventListener('mousedown', handler)
    return () => document.removeEventListener('mousedown', handler)
  }, [onClose])

  const folder = folders.find((f) => f.id === ctx.folderId)

  return (
    <div
      ref={ref}
      style={{
        position: 'fixed',
        top: ctx.y,
        left: ctx.x,
        zIndex: 9999,
        background: '#1a1a1a',
        border: '1px solid rgba(255,255,255,0.12)',
        borderRadius: 12,
        boxShadow: '0 8px 32px rgba(0,0,0,0.6)',
        padding: '6px 0',
        minWidth: 170,
      }}
    >
      <button
        onClick={() => onShowColor(ctx.folderId)}
        style={itemStyle}
        onMouseEnter={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'rgba(255,255,255,0.06)'
        }}
        onMouseLeave={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'transparent'
        }}
      >
        {t('shelf.changeColor')}
      </button>

      {showColorFor === ctx.folderId && folder && (
        <ColorPicker current={folder.color} onPick={(c) => onPickColor(ctx.folderId, c)} />
      )}

      <button
        onClick={() => folder && onRename(folder.id, folder.label)}
        style={itemStyle}
        onMouseEnter={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'rgba(255,255,255,0.06)'
        }}
        onMouseLeave={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'transparent'
        }}
      >
        {t('shelf.rename')}
      </button>

      <div style={{ height: 1, background: 'rgba(255,255,255,0.08)', margin: '4px 0' }} />

      <button
        onClick={() => onRemove(ctx.folderId)}
        style={{ ...itemStyle, color: '#ef5350' }}
        onMouseEnter={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'rgba(239,83,80,0.1)'
        }}
        onMouseLeave={(e) => {
          ;(e.currentTarget as HTMLElement).style.background = 'transparent'
        }}
      >
        {t('shelf.remove')}
      </button>
    </div>
  )
}
