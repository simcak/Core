import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { Button } from '@/components/ui/button.tsx'
import { Input } from '@/components/ui/input.tsx'
import { Label } from '@/components/ui/label.tsx'

type Author = { id: number; author_name: string }

type QueuedFile = {
  file: File
  status: 'pending' | 'uploading' | 'done' | 'error'
  progress: number
  error?: string
}

type MetaForm = {
  author_name: string
  publisher_name: string
  price: string
  currency: string
  language_code: string
  isbn: string
  product_status: string
}

type TranslationItem = {
  lang: string
  title: string
  description: string
}

const LANGUAGE_OPTIONS = [
  { code: 'en', label: 'English' },
  { code: 'ar', label: 'العربية' },
  { code: 'cs', label: 'Čeština' },
  { code: 'de', label: 'Deutsch' },
  { code: 'fr', label: 'Français' },
  { code: 'es', label: 'Español' },
]

export default function AdminBookFormPage() {
  const { t } = useTranslation()
  const navigate = useNavigate()
  const apiFetch = useApiFetch()

  const [authors, setAuthors] = useState<Author[]>([])
  const [meta, setMeta] = useState<MetaForm>({
    author_name: '',
    publisher_name: '',
    price: '',
    currency: 'EUR',
    language_code: '',
    isbn: '',
    product_status: 'draft',
  })
  const [translations, setTranslations] = useState<TranslationItem[]>([
    { lang: 'en', title: '', description: '' },
  ])
  const [coverFile, setCoverFile] = useState<File | null>(null)
  const [coverPreview, setCoverPreview] = useState<string | null>(null)
  const [audioQueue, setAudioQueue] = useState<QueuedFile[]>([])
  const [isSubmitting, setIsSubmitting] = useState(false)
  const [error, setError] = useState<string | null>(null)

  useEffect(() => {
    apiFetch('/api/authors')
      .then((r) => r.json())
      .then(setAuthors)
  }, [apiFetch])

  const setMetaField = (field: keyof MetaForm, value: string) =>
    setMeta((prev) => ({ ...prev, [field]: value }))

  const setTranslationField = (index: number, field: keyof TranslationItem, value: string) =>
    setTranslations((prev) => prev.map((tr, i) => (i === index ? { ...tr, [field]: value } : tr)))

  const addTranslation = () =>
    setTranslations((prev) => [...prev, { lang: '', title: '', description: '' }])

  const removeTranslation = (index: number) =>
    setTranslations((prev) => prev.filter((_, i) => i !== index))

  const handleCoverChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0] ?? null
    setCoverFile(file)
    setCoverPreview(file ? URL.createObjectURL(file) : null)
  }

  const handleAudioAdd = (e: React.ChangeEvent<HTMLInputElement>) => {
    const files = Array.from(e.target.files ?? [])
    const queued: QueuedFile[] = files.map((file) => ({
      file,
      status: 'pending',
      progress: 0,
    }))
    setAudioQueue((prev) => [...prev, ...queued])
    e.target.value = ''
  }

  const handleAudioRemove = (index: number) => {
    setAudioQueue((prev) => prev.filter((_, i) => i !== index))
  }

  const handleSubmit = async () => {
    const hasTitle = translations.some((tr) => tr.title.trim())
    if (!hasTitle || !meta.author_name || !meta.price) {
      setError('Author, price, and at least one translation with a title are required.')
      return
    }
    setIsSubmitting(true)
    setError(null)
    try {
      const bookRes = await apiFetch('/api/books', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          author_name: meta.author_name,
          publisher_name: meta.publisher_name || null,
          price: parseFloat(meta.price),
          currency: meta.currency,
          language_code: meta.language_code || null,
          isbn: meta.isbn || null,
          product_status: meta.product_status,
          translations: translations.map((tr) => ({
            lang: tr.lang,
            title: tr.title,
            description: tr.description || null,
            sample_url: null,
          })),
          category_ids: [],
        }),
      })
      if (!bookRes.ok) throw new Error(`Failed to create book: ${bookRes.status}`)
      const book = await bookRes.json()

      if (coverFile) {
        const fd = new FormData()
        fd.append('file', coverFile)
        const coverRes = await apiFetch(`/api/books/${book.id}/cover`, { method: 'POST', body: fd })
        if (!coverRes.ok) throw new Error(`Cover upload failed: ${coverRes.status}`)
      }

      for (let i = 0; i < audioQueue.length; i++) {
        const { file } = audioQueue[i]
        setAudioQueue((prev) =>
          prev.map((q, idx) => (idx === i ? { ...q, status: 'uploading' } : q))
        )
        try {
          const fd = new FormData()
          fd.append('file', file)
          fd.append('book_id', String(book.id))
          const res = await apiFetch('/api/audio/upload', { method: 'POST', body: fd })
          if (!res.ok) throw new Error(`Upload failed: ${res.status}`)
          setAudioQueue((prev) =>
            prev.map((q, idx) => (idx === i ? { ...q, status: 'done', progress: 100 } : q))
          )
        } catch (e) {
          setAudioQueue((prev) =>
            prev.map((q, idx) => (idx === i ? { ...q, status: 'error', error: String(e) } : q))
          )
        }
      }

      navigate(`/admin/books/${book.id}`)
    } catch (e) {
      setError(String(e))
    } finally {
      setIsSubmitting(false)
    }
  }

  return (
    <div className="flex flex-col gap-8 max-w-3xl">
      <div>
        <h1 className="text-2xl font-bold tracking-tight">{t('admin.books.newBook')}</h1>
        <p className="text-sm text-muted-foreground mt-1">{t('admin.books.newBookDesc')}</p>
      </div>

      {error && <p className="text-sm text-destructive">{error}</p>}

      <div className="grid grid-cols-2 gap-4">
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.authorLabel')}</Label>
          <Input
            list="authors-list"
            value={meta.author_name}
            onChange={(e) => setMetaField('author_name', e.target.value)}
            placeholder={t('admin.books.typeOrSelectAuthor')}
          />
          <datalist id="authors-list">
            {authors.map((a) => (
              <option key={a.id} value={a.author_name} />
            ))}
          </datalist>
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.publisher')}</Label>
          <Input
            value={meta.publisher_name}
            onChange={(e) => setMetaField('publisher_name', e.target.value)}
          />
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.price')} *</Label>
          <Input
            type="number"
            value={meta.price}
            onChange={(e) => setMetaField('price', e.target.value)}
          />
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.currency')}</Label>
          <select
            value={meta.currency}
            onChange={(e) => setMetaField('currency', e.target.value)}
            className="border rounded px-3 py-2 text-sm"
          >
            <option value="EUR">EUR</option>
            <option value="USD">USD</option>
            <option value="GBP">GBP</option>
          </select>
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.statusLabel')}</Label>
          <select
            value={meta.product_status}
            onChange={(e) => setMetaField('product_status', e.target.value)}
            className="border rounded px-3 py-2 text-sm"
          >
            <option value="draft">{t('admin.books.draft')}</option>
            <option value="active">{t('admin.books.active')}</option>
            <option value="archived">{t('admin.books.archived')}</option>
          </select>
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.isbn')}</Label>
          <Input value={meta.isbn} onChange={(e) => setMetaField('isbn', e.target.value)} />
        </div>
        <div className="flex flex-col gap-1.5">
          <Label>{t('admin.books.language')}</Label>
          <select
            value={meta.language_code}
            onChange={(e) => setMetaField('language_code', e.target.value)}
            className="border rounded px-3 py-2 text-sm"
          >
            <option value="">—</option>
            {LANGUAGE_OPTIONS.map((l) => (
              <option key={l.code} value={l.code}>
                {l.code.toUpperCase()} – {l.label}
              </option>
            ))}
          </select>
        </div>
      </div>

      <div className="flex flex-col gap-4">
        <div className="flex items-center justify-between">
          <Label className="text-base font-medium">{t('admin.books.translations')}</Label>
        </div>
        {translations.map((tr, i) => (
          <div key={i} className="rounded-md border p-4 flex flex-col gap-3">
            <div className="flex items-end justify-between gap-4">
              <div className="flex flex-col gap-1.5">
                <Label>{t('admin.books.translationCode')}</Label>
                <select
                  value={tr.lang}
                  onChange={(e) => setTranslationField(i, 'lang', e.target.value)}
                  className="border rounded px-3 py-2 text-sm max-w-[180px]"
                >
                  <option value="">—</option>
                  {LANGUAGE_OPTIONS.map((l) => (
                    <option key={l.code} value={l.code}>
                      {l.code.toUpperCase()} – {l.label}
                    </option>
                  ))}
                </select>
              </div>
              {translations.length > 1 && (
                <Button
                  variant="ghost"
                  size="sm"
                  className="text-destructive hover:text-destructive"
                  onClick={() => removeTranslation(i)}
                >
                  {t('admin.books.remove')}
                </Button>
              )}
            </div>
            <div className="flex flex-col gap-1.5">
              <Label>{t('admin.books.titleLabel')} *</Label>
              <Input
                value={tr.title}
                onChange={(e) => setTranslationField(i, 'title', e.target.value)}
              />
            </div>
            <div className="flex flex-col gap-1.5">
              <Label>{t('admin.books.description')}</Label>
              <textarea
                value={tr.description}
                onChange={(e) => setTranslationField(i, 'description', e.target.value)}
                rows={3}
                className="border rounded px-3 py-2 text-sm resize-none"
              />
            </div>
          </div>
        ))}
        <Button variant="outline" size="sm" onClick={addTranslation} className="w-fit">
          {t('admin.books.addTranslation')}
        </Button>
      </div>

      <div className="flex flex-col gap-2">
        <Label>{t('admin.books.coverImage')}</Label>
        <Input type="file" accept="image/jpeg,image/png,image/webp" onChange={handleCoverChange} />
        {coverPreview && (
          <img
            src={coverPreview}
            alt="Cover preview"
            className="h-40 w-auto object-contain rounded border"
          />
        )}
      </div>

      <div className="flex flex-col gap-3">
        <div className="flex items-center justify-between">
          <Label>{t('admin.books.audioFiles')}</Label>
          <label className="cursor-pointer">
            <span className="text-sm text-primary underline">{t('admin.books.addFiles')}</span>
            <input
              type="file"
              accept="audio/*"
              multiple
              className="hidden"
              onChange={handleAudioAdd}
            />
          </label>
        </div>
        {audioQueue.length === 0 && (
          <p className="text-sm text-muted-foreground">{t('admin.books.noFilesQueued')}</p>
        )}
        {audioQueue.map((q, i) => (
          <div key={i} className="flex items-center gap-3 text-sm">
            <span className="flex-1 truncate">{q.file.name}</span>
            {q.status === 'pending' && (
              <Button variant="ghost" size="sm" onClick={() => handleAudioRemove(i)}>
                {t('admin.books.remove')}
              </Button>
            )}
            {q.status === 'uploading' && (
              <span className="text-muted-foreground">{q.progress}%</span>
            )}
            {q.status === 'done' && <span className="text-green-600">{t('admin.books.done')}</span>}
            {q.status === 'error' && (
              <span className="text-destructive">{t('admin.books.error')}</span>
            )}
          </div>
        ))}
      </div>

      <div className="flex gap-3">
        <Button variant="outline" onClick={() => navigate('/admin/books')} disabled={isSubmitting}>
          {t('admin.books.cancel')}
        </Button>
        <Button onClick={handleSubmit} disabled={isSubmitting}>
          {isSubmitting ? t('admin.books.creating') : t('admin.books.createBook')}
        </Button>
      </div>
    </div>
  )
}
