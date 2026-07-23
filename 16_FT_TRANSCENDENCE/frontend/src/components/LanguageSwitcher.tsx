import { useTranslation } from 'react-i18next'
import i18n from '@/i18n'

const LANGUAGES = [
  { code: 'en', label: 'English' },
  { code: 'ar', label: 'العربية' },
  { code: 'cs', label: 'Čeština' },
]

export function LanguageSwitcher() {
  const { t } = useTranslation()
  return (
    <select
      value={i18n.language}
      onChange={(e) => void i18n.changeLanguage(e.target.value)}
      aria-label={t('language.switcher')}
      className="text-sm border rounded px-2 py-1 bg-background text-foreground"
    >
      {LANGUAGES.map((l) => (
        <option key={l.code} value={l.code}>
          {l.label}
        </option>
      ))}
    </select>
  )
}
