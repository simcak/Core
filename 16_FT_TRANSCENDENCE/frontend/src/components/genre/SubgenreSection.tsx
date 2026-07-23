// src/components/genre/SubgenreSection.tsx
import { useTranslation } from 'react-i18next'
import type { ApiCategory } from '../../pages/GenrePage'

// Emoji map for known subgenre names
const SUBGENRE_ICONS: Record<string, string> = {
  'Greek Classics': '🇬🇷',
  'Roman Literature': '📜',
  'Medieval Literature': '🏰',
  Enlightenment: '💡',
  'Personal Development': '🌱',
  Productivity: '📈',
  Mindfulness: '🧘',
  Leadership: '👑',
  Satire: '🎭',
  'Humorous Memoir': '😂',
  Parody: '🤣',
  'Psychological Thriller': '🧠',
  'Political Thriller': '🏛️',
  'Legal Thriller': '⚖️',
  'Spy Thriller': '🕵️',
  'Ancient Philosophy': '🏺',
  'Modern Philosophy': '🧐',
  Ethics: '😇',
  Existentialism: '🤔',
  'Epic Fantasy': '⚔️',
  'Dark Fantasy': '🌑',
  'Urban Fantasy': '🌆',
  'Fairy Tales': '🧚',
  Mythology: '🏛️',
  'Space Opera': '🌌',
  Cyberpunk: '🤖',
  'Hard Sci-Fi': '🔬',
  Dystopian: '🏚️',
  'Time Travel': '⏳',
  'Cozy Mystery': '☕',
  Thriller: '🔪',
  Noir: '🌧️',
  Crime: '🚔',
  'Contemporary Romance': '🏙️',
  'Historical Romance': '🏰',
  'Paranormal Romance': '👻',
  'Romantic Comedy': '😂',
  'Psychological Horror': '🧠',
  'Supernatural Horror': '👻',
  'Cosmic Horror': '🌀',
  Memoir: '✍️',
  Autobiography: '🪞',
  'Political Bio': '🏛️',
  'Ancient History': '🏺',
  'Modern History': '📰',
  'Military History': '⚔️',
}

interface SubgenreSectionProps {
  subgenres: ApiCategory[]
  activeId: number | null
  color: string
  onSelect: (id: number | null) => void
}

export default function SubgenreSection({
  subgenres,
  activeId,
  color,
  onSelect,
}: SubgenreSectionProps) {
  const { t } = useTranslation()
  if (!subgenres.length) return null

  return (
    <div className="flex flex-col gap-3">
      <h2 className="text-xl font-semibold text-white">{t('genre.subgenres')}</h2>

      <div className="flex gap-3 overflow-x-auto pb-2" style={{ scrollbarWidth: 'none' }}>
        {/* "All" pill */}
        <button
          onClick={() => onSelect(null)}
          className="flex-shrink-0 px-4 py-2 rounded-full text-sm font-medium transition-all duration-200"
          style={
            activeId === null
              ? { background: color, color: '#fff' }
              : { background: '#1f2937', color: '#9ca3af' }
          }
        >
          {t('genre.all')}
        </button>

        {subgenres.map((sub) => (
          <button
            key={sub.id}
            onClick={() => onSelect(sub.id === activeId ? null : sub.id)}
            className="flex-shrink-0 flex items-center gap-2 px-4 py-2 rounded-full text-sm font-medium transition-all duration-200 whitespace-nowrap"
            style={
              activeId === sub.id
                ? { background: color, color: '#fff' }
                : { background: '#1f2937', color: '#9ca3af' }
            }
          >
            {SUBGENRE_ICONS[sub.name] && <span>{SUBGENRE_ICONS[sub.name]}</span>}
            {sub.name}
          </button>
        ))}
      </div>
    </div>
  )
}
