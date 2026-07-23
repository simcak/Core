import { useState, useEffect, useCallback } from 'react'
import { Link, useNavigate, useParams } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import type { ColumnDef } from '@tanstack/react-table'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { DataTable } from '@/components/common/DataTable.tsx'
import { Button } from '@/components/ui/button.tsx'
import { Input } from '@/components/ui/input.tsx'
import { Label } from '@/components/ui/label.tsx'
import UploadAudioDialog from '@/components/audio/UploadAudioDialog.tsx'
import ConfirmDeleteDialog from '@/components/common/ConfirmDeleteDialog.tsx'
import {
  Card,
  CardAction,
  CardContent,
  CardFooter,
  CardHeader,
  CardTitle,
} from '@/components/ui/card.tsx'
import { Check } from 'lucide-react'
import { toast } from 'sonner'

type Author = { id: number; author_name: string }

type Translation = {
  lang: string
  title: string
  description: string | null
  cover_image_filename: string | null
  sample_url: string | null
}

type BookDetail = {
  id: number
  author: { author_name: string }
  publisher: { publisher_name: string } | null
  translations: Translation[]
  price: number
  currency: string
  language_code: string | null
  isbn: string | null
  product_status: string
}

type AudioFile = {
  id: number
  book_id: number
  original_filename: string
  file_size: number
  mime_type: string
  status: string
  duration_seconds: number | null
  created_at: string
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

type TranslationForm = {
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

export default function AdminBookPage() {
  const { t } = useTranslation()
  const { bookId } = useParams<{ bookId: string }>()
  const navigate = useNavigate()
  const apiFetch = useApiFetch()

  const [book, setBook] = useState<BookDetail | null>(null)
  const [authors, setAuthors] = useState<Author[]>([])
  const [files, setFiles] = useState<AudioFile[]>([])
  const [loading, setLoading] = useState(true)
  const [meta, setMeta] = useState<MetaForm>({
    author_name: '',
    publisher_name: '',
    price: '',
    currency: 'EUR',
    language_code: '',
    isbn: '',
    product_status: 'draft',
  })
  const [translations, setTranslations] = useState<TranslationForm[]>([])
  const [coverFile, setCoverFile] = useState<File | null>(null)
  const [coverPreview, setCoverPreview] = useState<string | null>(null)
  const [isSaving, setIsSaving] = useState(false)
  const [isSavingCover, setIsSavingCover] = useState(false)
  const [saveSuccess, setSaveSuccess] = useState(false)
  const [coverSaveSuccess, setCoverSaveSuccess] = useState(false)
  const [uploadOpen, setUploadOpen] = useState(false)
  const [deleteAudioTarget, setDeleteAudioTarget] = useState<AudioFile | null>(null)
  const [isDeletingAudio, setIsDeletingAudio] = useState(false)
  const [softDeleteOpen, setSoftDeleteOpen] = useState(false)
  const [isSoftDeleting, setIsSoftDeleting] = useState(false)
  const [permanentDeleteOpen, setPermanentDeleteOpen] = useState(false)
  const [isPermanentDeleting, setIsPermanentDeleting] = useState(false)

  const fetchFiles = useCallback(() => {
    apiFetch(`/api/audio/files/${bookId}`)
      .then((r) => r.json())
      .then(setFiles)
  }, [apiFetch, bookId])

  useEffect(() => {
    Promise.all([
      apiFetch(`/api/books/${bookId}`).then((r) => r.json()),
      apiFetch(`/api/audio/files/${bookId}`).then((r) => r.json()),
      apiFetch('/api/authors').then((r) => r.json()),
    ]).then(([bookData, filesData, authorsData]) => {
      setBook(bookData)
      setMeta({
        author_name: bookData.author.author_name,
        publisher_name: bookData.publisher?.publisher_name ?? '',
        price: String(bookData.price),
        currency: bookData.currency,
        language_code: bookData.language_code ?? '',
        isbn: bookData.isbn ?? '',
        product_status: bookData.product_status,
      })
      setTranslations(
        bookData.translations.map((tr: Translation) => ({
          lang: tr.lang,
          title: tr.title,
          description: tr.description ?? '',
        }))
      )
      setFiles(filesData)
      setAuthors(authorsData)
      setLoading(false)
    })
  }, [apiFetch, bookId])

  const setMetaField = (field: keyof MetaForm, value: string) =>
    setMeta((prev) => ({ ...prev, [field]: value }))

  const setTranslationField = (index: number, field: keyof TranslationForm, value: string) =>
    setTranslations((prev) => prev.map((tr, i) => (i === index ? { ...tr, [field]: value } : tr)))

  const addTranslation = () =>
    setTranslations((prev) => [...prev, { lang: '', title: '', description: '' }])

  const removeTranslation = (index: number) =>
    setTranslations((prev) => prev.filter((_, i) => i !== index))

  const handleSave = async () => {
    setIsSaving(true)
    try {
      const res = await apiFetch(`/api/books/${bookId}`, {
        method: 'PUT',
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
          })),
        }),
      })
      if (!res.ok) throw new Error(`Failed to save: ${res.status}`)
      const updated = await res.json()
      setBook(updated)
      setSaveSuccess(true)
      toast.success(t('admin.books.savedSuccess'))
      setTimeout(() => setSaveSuccess(false), 2000)
    } catch (e) {
      toast.error(String(e))
    } finally {
      setIsSaving(false)
    }
  }

  const handleCoverChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0] ?? null
    setCoverFile(file)
    setCoverPreview(file ? URL.createObjectURL(file) : null)
  }

  const handleCoverSave = async () => {
    if (!coverFile) return
    setIsSavingCover(true)
    try {
      const fd = new FormData()
      fd.append('file', coverFile)
      const res = await apiFetch(`/api/books/${bookId}/cover`, { method: 'POST', body: fd })
      if (!res.ok) throw new Error(`Cover upload failed: ${res.status}`)
      setCoverFile(null)
      setCoverPreview(null)
      setCoverSaveSuccess(true)
      toast.success(t('admin.books.coverSavedSuccess'))
      setTimeout(() => setCoverSaveSuccess(false), 2000)
    } catch (e) {
      toast.error(String(e))
    } finally {
      setIsSavingCover(false)
    }
  }

  const handleDeleteAudio = async () => {
    if (!deleteAudioTarget) return
    setIsDeletingAudio(true)
    try {
      const res = await apiFetch(`/api/audio/files/${deleteAudioTarget.id}`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Delete failed: ${res.status}`)
      setDeleteAudioTarget(null)
      fetchFiles()
      toast.success(t('admin.books.audioDeletedSuccess'))
    } catch (e) {
      toast.error(String(e))
    } finally {
      setIsDeletingAudio(false)
    }
  }

  const handleSoftDelete = async () => {
    setIsSoftDeleting(true)
    try {
      const res = await apiFetch(`/api/books/${bookId}`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Delete failed: ${res.status}`)
      const updated = await res.json()
      setBook(updated)
      setMeta((prev) => ({ ...prev, product_status: 'deleted' }))
      setSoftDeleteOpen(false)
      toast.success(t('admin.books.bookMarkedDeleted'))
    } catch (e) {
      toast.error(String(e))
    } finally {
      setIsSoftDeleting(false)
    }
  }

  const handlePermanentDelete = async () => {
    setIsPermanentDeleting(true)
    try {
      const res = await apiFetch(`/api/books/${bookId}/permanent`, { method: 'DELETE' })
      if (!res.ok) throw new Error(`Permanent delete failed: ${res.status}`)
      navigate('/admin/books')
    } catch (e) {
      console.error(e)
      setIsPermanentDeleting(false)
    }
  }

  const columns: ColumnDef<AudioFile>[] = [
    { accessorKey: 'id', header: 'ID' },
    { accessorKey: 'original_filename', header: t('admin.books.filename') },
    {
      accessorKey: 'file_size',
      header: t('admin.books.size'),
      cell: ({ row }) => {
        const val = row.getValue<number>('file_size')
        return `${(val / 1024 / 1024).toFixed(2)} MB`
      },
    },
    { accessorKey: 'duration_seconds', header: t('admin.books.duration') },
    { accessorKey: 'status', header: t('admin.books.statusLabel') },
    {
      id: 'actions',
      header: t('admin.books.actions'),
      cell: ({ row }) => (
        <Button
          variant="ghost"
          size="sm"
          className="text-destructive hover:text-destructive"
          onClick={() => setDeleteAudioTarget(row.original)}
        >
          {t('admin.books.delete')}
        </Button>
      ),
    },
  ]

  if (loading) return <p className="text-sm text-muted-foreground">{t('common.loading')}</p>

  const isDeleted = book?.product_status === 'deleted'
  const displayTitle = translations[0]?.title || `Book #${bookId}`

  return (
    <div className="flex flex-col gap-8">
      <div className="flex items-start justify-between">
        <div className="flex flex-col gap-1">
          <Button
            variant="ghost"
            size="sm"
            asChild
            className="-ml-2 w-fit text-muted-foreground hover:text-foreground"
          >
            <Link to="/admin/books">{t('admin.books.backToBooks')}</Link>
          </Button>
          <h1 className="text-2xl font-bold tracking-tight">{displayTitle}</h1>
          <p className="text-sm text-muted-foreground">
            #{bookId} · {meta.product_status} · {meta.currency} {meta.price}
          </p>
        </div>
        {!isDeleted && (
          <Button variant="destructive" size="sm" onClick={() => setSoftDeleteOpen(true)}>
            {t('admin.books.deleteBook')}
          </Button>
        )}
      </div>

      <div className="grid grid-cols-3 gap-6">
        <div className="col-span-2 flex flex-col gap-6">
          <Card className="bg-transparent">
            <CardHeader>
              <CardTitle>{t('admin.books.bookDetails')}</CardTitle>
            </CardHeader>
            <CardContent className="flex flex-col gap-4">
              <div className="grid grid-cols-2 gap-4">
                <div className="flex flex-col gap-1.5">
                  <Label>{t('admin.books.authorLabel')}</Label>
                  <Input
                    list="authors-list"
                    value={meta.author_name}
                    onChange={(e) => setMetaField('author_name', e.target.value)}
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
              </div>
              <div className="flex flex-col gap-1.5">
                <Label>{t('admin.books.language')}</Label>
                <select
                  value={meta.language_code}
                  onChange={(e) => setMetaField('language_code', e.target.value)}
                  className="border rounded px-3 py-2 text-sm max-w-xs"
                >
                  <option value="">—</option>
                  {LANGUAGE_OPTIONS.map((l) => (
                    <option key={l.code} value={l.code}>
                      {l.code.toUpperCase()} – {l.label}
                    </option>
                  ))}
                </select>
              </div>
            </CardContent>
          </Card>

          <Card className="bg-transparent">
            <CardHeader>
              <CardTitle>{t('admin.books.translations')}</CardTitle>
            </CardHeader>
            <CardContent className="flex flex-col gap-6">
              {translations.length === 0 && (
                <p className="text-sm text-muted-foreground">{t('admin.books.noTranslations')}</p>
              )}
              {translations.map((tr, i) => (
                <div key={i} className="rounded-md border p-4 flex flex-col gap-3">
                  <div className="flex items-center justify-between">
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
                    <Button
                      variant="ghost"
                      size="sm"
                      className="text-destructive hover:text-destructive self-end"
                      onClick={() => removeTranslation(i)}
                    >
                      {t('admin.books.remove')}
                    </Button>
                  </div>
                  <div className="flex flex-col gap-1.5">
                    <Label>{t('admin.books.titleLabel')}</Label>
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
            </CardContent>
          </Card>

          <Card className="bg-transparent">
            <CardHeader>
              <CardTitle>{t('admin.books.pricingMetadata')}</CardTitle>
            </CardHeader>
            <CardContent className="flex flex-col gap-4">
              <div className="grid grid-cols-2 gap-4">
                <div className="flex flex-col gap-1.5">
                  <Label>{t('admin.books.price')}</Label>
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
              </div>
              <div className="flex flex-col gap-1.5">
                <Label>{t('admin.books.statusLabel')}</Label>
                <select
                  value={meta.product_status}
                  onChange={(e) => setMetaField('product_status', e.target.value)}
                  className="border rounded px-3 py-2 text-sm max-w-xs"
                >
                  <option value="draft">{t('admin.books.draft')}</option>
                  <option value="active">{t('admin.books.active')}</option>
                  <option value="archived">{t('admin.books.archived')}</option>
                  <option value="deleted">{t('admin.books.deleted')}</option>
                </select>
              </div>
              <div className="flex flex-col gap-1.5">
                <Label>{t('admin.books.isbn')}</Label>
                <Input value={meta.isbn} onChange={(e) => setMetaField('isbn', e.target.value)} />
              </div>
            </CardContent>
            <CardFooter className="justify-end">
              <Button
                onClick={handleSave}
                disabled={isSaving || saveSuccess}
                className={saveSuccess ? 'bg-green-600 hover:bg-green-600 text-white' : ''}
              >
                {isSaving ? (
                  t('admin.books.saving')
                ) : saveSuccess ? (
                  <>
                    <Check className="w-4 h-4 mr-1.5" />
                    {t('admin.books.saved')}
                  </>
                ) : (
                  t('admin.books.saveChanges')
                )}
              </Button>
            </CardFooter>
          </Card>
        </div>

        <div className="col-span-1 self-start sticky top-4">
          <Card className="bg-transparent">
            <CardHeader>
              <CardTitle>{t('admin.books.coverImage')}</CardTitle>
            </CardHeader>
            <CardContent className="flex flex-col gap-3">
              <div className="rounded-lg border bg-muted overflow-hidden aspect-3/4 flex items-center justify-center relative">
                {coverPreview ? (
                  <>
                    <img
                      src={coverPreview}
                      alt="New cover preview"
                      className="w-full h-full object-cover"
                    />
                    <span className="absolute top-2 left-2 bg-black/60 text-white text-xs px-2 py-0.5 rounded">
                      {t('admin.books.preview')}
                    </span>
                  </>
                ) : book?.translations[0]?.cover_image_filename ? (
                  <img
                    src={`/covers/${book?.translations[0]?.cover_image_filename}`}
                    alt="Book cover"
                    className="w-full h-full object-cover"
                  />
                ) : (
                  <p className="text-xs text-muted-foreground">{t('admin.books.noCover')}</p>
                )}
              </div>
              <Input
                type="file"
                accept="image/jpeg,image/png,image/webp"
                onChange={handleCoverChange}
              />
            </CardContent>
            {(coverFile || coverSaveSuccess) && (
              <CardFooter className="justify-end">
                <Button
                  onClick={handleCoverSave}
                  disabled={isSavingCover || coverSaveSuccess}
                  className={coverSaveSuccess ? 'bg-green-600 hover:bg-green-600 text-white' : ''}
                >
                  {isSavingCover ? (
                    t('admin.books.uploading')
                  ) : coverSaveSuccess ? (
                    <>
                      <Check className="w-4 h-4 mr-1.5" />
                      {t('admin.books.saved')}
                    </>
                  ) : (
                    t('admin.books.saveCover')
                  )}
                </Button>
              </CardFooter>
            )}
          </Card>
        </div>
      </div>

      <Card className="bg-transparent">
        <CardHeader>
          <CardTitle>{t('admin.books.audioFiles')}</CardTitle>
          <CardAction>
            <Button size="sm" onClick={() => setUploadOpen(true)}>
              {t('admin.books.uploadFile')}
            </Button>
          </CardAction>
        </CardHeader>
        <CardContent>
          <DataTable columns={columns} data={files} />
        </CardContent>
      </Card>

      {isDeleted && (
        <div className="rounded-lg border-2 border-destructive bg-destructive/5 p-6 flex flex-col gap-4">
          <div className="flex flex-col gap-1">
            <h2 className="text-lg font-semibold text-destructive">
              {t('admin.books.dangerZone')}
            </h2>
            <p className="text-sm text-muted-foreground">{t('admin.books.dangerZoneDesc')}</p>
          </div>
          <div>
            <Button variant="destructive" onClick={() => setPermanentDeleteOpen(true)}>
              {t('admin.books.permanentDelete')}
            </Button>
          </div>
        </div>
      )}

      <UploadAudioDialog
        bookId={bookId!}
        open={uploadOpen}
        onOpenChange={setUploadOpen}
        onSuccess={fetchFiles}
      />
      <ConfirmDeleteDialog
        open={!!deleteAudioTarget}
        onOpenChange={(open) => {
          if (!open) setDeleteAudioTarget(null)
        }}
        title="Delete audio file?"
        description={`This will permanently remove "${deleteAudioTarget?.original_filename}".`}
        onConfirm={handleDeleteAudio}
        isLoading={isDeletingAudio}
      />
      <ConfirmDeleteDialog
        open={softDeleteOpen}
        onOpenChange={setSoftDeleteOpen}
        title="Mark book as deleted?"
        description={`Book #${bookId} will be marked as deleted and hidden from users. You can restore it by changing its status back to draft or active.`}
        onConfirm={handleSoftDelete}
        isLoading={isSoftDeleting}
      />
      <ConfirmDeleteDialog
        open={permanentDeleteOpen}
        onOpenChange={setPermanentDeleteOpen}
        title="Permanently delete book?"
        description={`This will permanently remove Book #${bookId} and all its audio files. This cannot be undone.`}
        onConfirm={handlePermanentDelete}
        isLoading={isPermanentDeleting}
      />
    </div>
  )
}
