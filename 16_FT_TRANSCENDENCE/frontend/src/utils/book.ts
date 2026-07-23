export interface BookTranslation {
  lang: string
  title: string
  description: string | null
  cover_image_filename: string | null
  sample_url: string | null
}

const normalizeLang = (lang: string) => lang.split('-')[0].toLowerCase()

const findTranslation = (translations: BookTranslation[], lang: string) =>
  translations.find((t) => normalizeLang(t.lang) === normalizeLang(lang)) ?? translations[0]

export const getTitle = (translations: BookTranslation[], lang = 'en') =>
  findTranslation(translations, lang)?.title ?? '—'

export const getDescription = (translations: BookTranslation[], lang = 'en') =>
  findTranslation(translations, lang)?.description ?? ''

export const getCover = (translations: BookTranslation[], lang = 'en') =>
  findTranslation(translations, lang)?.cover_image_filename ?? null

// Returns a URL-safe slug for routing. Prefers English title; falls back to the
// first translation that produces a non-empty slug (avoids Arabic-only titles
// being stripped to an empty string by toSlug).
export const getBookSlug = (translations: BookTranslation[]): string => {
  const toSlug = (s: string) =>
    s
      .toLowerCase()
      .replace(/\s+/g, '-')
      .replace(/[^a-z0-9-]/g, '')

  const enTitle = translations.find((t) => normalizeLang(t.lang) === 'en')?.title
  if (enTitle) {
    const s = toSlug(enTitle)
    if (s) return s
  }
  for (const t of translations) {
    const s = toSlug(t.title)
    if (s) return s
  }
  return `book-${translations[0]?.lang ?? 'unknown'}`
}
