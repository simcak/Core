import i18n from 'i18next'
import { initReactI18next } from 'react-i18next'
import en from '../public/locales/en/translation.json'
import ar from '../public/locales/ar/translation.json'
import cs from '../public/locales/cs/translation.json'

const savedLang = localStorage.getItem('lang') ?? 'en'

void i18n.use(initReactI18next).init({
  resources: {
    en: { translation: en },
    ar: { translation: ar },
    cs: { translation: cs },
  },
  lng: savedLang,
  fallbackLng: 'en',
  interpolation: { escapeValue: false },
  returnNull: false,
})

i18n.on('languageChanged', (lang) => {
  localStorage.setItem('lang', lang)
  document.documentElement.lang = lang
  document.documentElement.dir = lang === 'ar' ? 'rtl' : 'ltr'
})

// Apply direction on initial load
document.documentElement.lang = savedLang
document.documentElement.dir = savedLang === 'ar' ? 'rtl' : 'ltr'

export default i18n
