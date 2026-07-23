import { useTranslation } from 'react-i18next'

export function useBookLocale(): string {
  const { i18n } = useTranslation()
  //   return userSettings.preferredBookLang ?? i18n.language // TODO: Later
  return i18n.language
}
