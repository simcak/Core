import { useState } from 'react'
import { useTranslation } from 'react-i18next'
import type { BookTranslation } from './types.ts'
import { getDescription } from '../../utils/book.ts'

interface BookDescriptionProps {
  translations: BookTranslation[]
  lang?: string
  previewLength?: number
}

export default function BookDescription({
  translations,
  lang = 'en',
  previewLength = 500,
}: BookDescriptionProps) {
  const { t } = useTranslation()
  const [expanded, setExpanded] = useState(false)

  const description = getDescription(translations, lang)

  if (!description) return null

  const isLong = description.length > previewLength
  const displayed = expanded || !isLong ? description : description.slice(0, previewLength)

  return (
    <div className="flex flex-col gap-3">
      <h2 className="text-xl font-semibold text-white">{t('book.description')}</h2>
      <div className="text-neutral-300 text-sm leading-relaxed">
        <p>
          {displayed}
          {!expanded && isLong && <span className="text-neutral-500"> …</span>}
        </p>
        {isLong && (
          <button
            onClick={() => setExpanded((e) => !e)}
            className="mt-2 text-neutral-400 hover:text-white text-sm underline underline-offset-2 transition-colors"
          >
            {expanded ? t('book.showLess') : t('book.showMore')}
          </button>
        )}
      </div>
    </div>
  )
}
