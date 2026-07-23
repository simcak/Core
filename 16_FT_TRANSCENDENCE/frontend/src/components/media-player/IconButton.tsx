import { useState } from 'react'

interface IconButtonProps {
  children: React.ReactNode
  onClick?: (e: React.MouseEvent) => void
  title?: string
  size?: 'sm' | 'md' | 'lg'
  active?: boolean
  disabled?: boolean
}

export function IconButton({
  children,
  onClick,
  title,
  size = 'md',
  active = false,
  disabled = false,
}: IconButtonProps) {
  const [hovered, setHovered] = useState(false)

  const padding = size === 'sm' ? '4px' : size === 'lg' ? '10px' : '7px'
  const color = disabled
    ? 'rgba(255,255,255,0.2)'
    : active || hovered
      ? '#f97316'
      : 'rgba(255,255,255,0.8)'

  return (
    <button
      title={title}
      onClick={onClick}
      disabled={disabled}
      onMouseEnter={() => setHovered(true)}
      onMouseLeave={() => setHovered(false)}
      style={{
        background: 'none',
        border: 'none',
        cursor: disabled ? 'default' : 'pointer',
        color,
        padding,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        transition: 'color 0.15s ease',
        lineHeight: 1,
        flexShrink: 0,
      }}
    >
      {children}
    </button>
  )
}
