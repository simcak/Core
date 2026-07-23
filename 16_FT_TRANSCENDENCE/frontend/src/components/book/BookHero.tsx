import { useState } from 'react'
import { Link } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { Share2, Check, ListMusic } from 'lucide-react'
import type { Book } from './types.ts'
import AddToListMenu from './AddToListMenu.tsx'
import { getTitle, getCover } from '../../utils/book.ts'
import { useAudioContext } from '../media-player'
import { generateBookBackground } from '../../utils/randBackgroundGen'
import type { PublicAudioFile } from '../../pages/BookPage.tsx'
import { Dialog, DialogContent, DialogHeader, DialogTitle } from '../ui/dialog.tsx'

const LANG_FLAGS: Record<string, string> = {
  en: '🇬🇧',
  cs: '🇨🇿',
  sk: '🇸🇰',
  es: '🇪🇸',
  fr: '🇫🇷',
  de: '🇩🇪',
  ar: '🇪🇬',
}

interface BookHeroProps {
  book: Book
  selectedLang: string
  onLangChange: (lang: string) => void
  audioFiles: PublicAudioFile[]
}

export default function BookHero({ book, selectedLang, onLangChange, audioFiles }: BookHeroProps) {
  const { t } = useTranslation()

  const title = getTitle(book.translations, selectedLang)
  const cover = getCover(book.translations, selectedLang)

  return (
    <div className="flex flex-col gap-6">
      {/* Title + author */}
      <div>
        <h1 className="text-3xl font-bold text-white leading-tight">{title}</h1>
        <Link
          to={`/author/${book.author.id}`}
          className="mt-1 inline-block text-neutral-400 hover:text-orange-400 hover:underline transition-colors"
        >
          {book.author.author_name}
        </Link>
      </div>

      {/* Main hero row */}
      <div className="flex gap-6 flex-wrap lg:flex-nowrap">
        {/* Cover */}
        <div className="flex-shrink-0">
          <div
            className="w-48 h-64 rounded-lg shadow-2xl overflow-hidden"
            style={{ background: generateBookBackground(book.id) }}
          >
            {cover && (
              <img src={`/covers/${cover}`} alt={title} className="w-full h-full object-cover" />
            )}
          </div>
        </div>

        {/* Metadata */}
        <div className="flex-1 flex flex-col gap-3">
          {book.publisher && (
            <MetaRow
              label={t('book.publisher')}
              value={
                <Link
                  to={`/publisher/${book.publisher.id}`}
                  className="hover:text-orange-400 hover:underline transition-colors"
                >
                  {book.publisher.publisher_name}
                </Link>
              }
            />
          )}
          {book.categories.length > 0 && (
            <MetaRow
              label={t('book.categories')}
              value={book.categories.map((c) => c.category_name).join(', ')}
            />
          )}
          {book.isbn && <MetaRow label={t('book.isbn')} value={book.isbn} />}

          {/* Action buttons */}
          <div className="flex items-center gap-3 mt-2">
            <AddToListMenu bookId={book.id} />
            <ShareButton title={title} />
          </div>
        </div>

        {/* Buy + language + listen panel */}
        <div className="flex-shrink-0 w-64">
          <div className="border border-dashed border-neutral-600 rounded-xl p-4 flex flex-col gap-4">
            {/* Language selector */}
            {book.translations.length > 1 && (
              <div className="flex items-start gap-3">
                <span className="text-neutral-400 text-sm w-20 flex-shrink-0 mt-0.5">
                  {t('book.language')}
                </span>
                <div className="flex gap-1.5 flex-wrap">
                  {book.translations.map((t) => (
                    <button
                      key={t.lang}
                      onClick={() => onLangChange(t.lang)}
                      title={t.lang}
                      className={`text-base transition-transform hover:scale-110 ${
                        selectedLang === t.lang ? 'scale-110' : 'opacity-70'
                      }`}
                    >
                      {LANG_FLAGS[t.lang] ?? t.lang.toUpperCase()}
                    </button>
                  ))}
                </div>
              </div>
            )}

            {/* Listen button */}
            <ListenButton
              book={book}
              title={title}
              coverUrl={cover ? `/covers/${cover}` : null}
              audioFiles={audioFiles}
            />

            {/* Buy button */}
            {/* <BuyButton price={book.price} currency={book.currency} /> */}
          </div>
        </div>
      </div>
    </div>
  )
}

// ─── Share button ──────────────────────────────────────────────────────────────

function copyToClipboard(text: string): Promise<void> {
  if (navigator.clipboard?.writeText) {
    return navigator.clipboard.writeText(text)
  }
  return new Promise((resolve, reject) => {
    const ta = document.createElement('textarea')
    ta.value = text
    ta.style.cssText = 'position:fixed;opacity:0'
    document.body.appendChild(ta)
    ta.focus()
    ta.select()
    const ok = document.execCommand('copy')
    document.body.removeChild(ta)
    if (ok) resolve()
    else reject(new Error('execCommand copy failed'))
  })
}

function ShareButton({ title }: { title: string }) {
  const { t } = useTranslation()
  const [copied, setCopied] = useState(false)

  const handleShare = async () => {
    const url = window.location.href
    try {
      if (navigator.share) {
        await navigator.share({ title, url })
      } else {
        await copyToClipboard(url)
        setCopied(true)
        setTimeout(() => setCopied(false), 2000)
      }
    } catch {
      // user cancelled share or copy failed — do nothing
    }
  }

  return (
    <div className="relative">
      <button
        onClick={handleShare}
        className="w-9 h-9 rounded-full border border-neutral-600 flex items-center justify-center text-white hover:border-neutral-400 hover:bg-neutral-800 transition-colors"
        title={copied ? t('book.linkCopied') : t('book.share')}
      >
        {copied ? <Check className="w-4 h-4 text-green-400" /> : <Share2 className="w-4 h-4" />}
      </button>
      {copied && (
        <div className="absolute left-1/2 top-full z-20 mt-2 -translate-x-1/2 whitespace-nowrap rounded-md border border-neutral-700 bg-neutral-900 px-3 py-1.5 text-xs font-medium text-white shadow-lg">
          {t('book.linkCopied')}
        </div>
      )}
    </div>
  )
}

// ─── Listen button + track picker ─────────────────────────────────────────────

interface ListenButtonProps {
  book: Book
  title: string
  coverUrl: string | null
  audioFiles: PublicAudioFile[]
}

function trackLabel(filename: string, index: number): string {
  const base = filename.replace(/\.[^.]+$/, '')
  const parts = base.split('_')
  const words = (parts.length > 2 ? parts.slice(2) : parts).join(' ').replace(/-/g, ' ').trim()
  return words || `Track ${index + 1}`
}

function formatDuration(seconds: number | null): string | null {
  if (seconds == null) return null
  const m = Math.floor(seconds / 60)
  const s = Math.floor(seconds % 60)
  return `${m}:${s.toString().padStart(2, '0')}`
}

function ListenButton({ book, title, coverUrl, audioFiles }: ListenButtonProps) {
  const { t } = useTranslation()
  const { loadBook, resumePlayback, goToFile, track, playing, currentFileIdx } = useAudioContext()
  const [loading, setLoading] = useState(false)
  const [unavailable, setUnavailable] = useState(false)
  const [dialogOpen, setDialogOpen] = useState(false)

  const noAudio = audioFiles.length === 0
  const bookInPlayer = track?.bookId === String(book.id)
  const nowPlaying = bookInPlayer && playing
  const paused = bookInPlayer && !playing

  const startTrack = async (fileIdx: number) => {
    if (bookInPlayer) {
      goToFile(fileIdx)
      return
    }
    setLoading(true)
    setUnavailable(false)
    try {
      await loadBook(book.id, { title, author: book.author.author_name, coverUrl }, fileIdx)
    } catch {
      setUnavailable(true)
    } finally {
      setLoading(false)
    }
  }

  const handleMainClick = async () => {
    if (noAudio || loading || nowPlaying) return
    if (paused) {
      resumePlayback()
      return
    }
    await startTrack(0)
  }

  if (unavailable) {
    return <p className="text-neutral-500 text-sm text-center py-2">{t('book.noAudio')}</p>
  }

  return (
    <div className="flex flex-col gap-2">
      <button
        onClick={handleMainClick}
        disabled={loading || noAudio}
        title={noAudio ? t('book.noAudio') : undefined}
        className={`w-full flex items-center justify-center gap-2 rounded-xl px-4 py-3 font-medium transition-colors disabled:opacity-60 disabled:cursor-not-allowed ${
          noAudio
            ? 'bg-neutral-700 text-neutral-400'
            : nowPlaying
              ? 'bg-orange-500/20 border border-orange-500/40 text-orange-400 cursor-default'
              : 'bg-orange-500 hover:bg-orange-600 active:bg-orange-700 text-white cursor-pointer'
        }`}
      >
        {loading ? (
          <>
            <svg className="w-4 h-4 animate-spin" fill="none" viewBox="0 0 24 24">
              <circle
                className="opacity-25"
                cx="12"
                cy="12"
                r="10"
                stroke="currentColor"
                strokeWidth="4"
              />
              <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8v8H4z" />
            </svg>
            <span>{t('book.loading')}</span>
          </>
        ) : noAudio ? (
          <span>{t('book.noAudio')}</span>
        ) : nowPlaying ? (
          <>
            <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 24 24">
              <rect x="6" y="4" width="4" height="16" rx="1" />
              <rect x="14" y="4" width="4" height="16" rx="1" />
            </svg>
            <span>{t('book.nowPlaying')}</span>
          </>
        ) : paused ? (
          <>
            <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 24 24">
              <path d="M8 5v14l11-7z" />
            </svg>
            <span>{t('book.resume')}</span>
          </>
        ) : (
          <>
            <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 24 24">
              <path d="M8 5v14l11-7z" />
            </svg>
            <span>{t('book.listen')}</span>
          </>
        )}
      </button>

      {audioFiles.length > 1 && (
        <button
          onClick={() => setDialogOpen(true)}
          className="flex items-center justify-center gap-1.5 text-xs text-neutral-400 hover:text-orange-400 transition-colors py-0.5"
        >
          <ListMusic className="w-3.5 h-3.5" />
          {t('book.tracksAvailable', { count: audioFiles.length })}
        </button>
      )}

      <Dialog open={dialogOpen} onOpenChange={setDialogOpen}>
        <DialogContent className="max-w-sm">
          <DialogHeader>
            <DialogTitle>{t('book.audioTracks')}</DialogTitle>
          </DialogHeader>
          <div className="flex flex-col gap-0.5 mt-1">
            {audioFiles.map((file, idx) => {
              const isCurrentTrack = bookInPlayer && currentFileIdx === idx
              const label = trackLabel(file.original_filename, idx)
              const duration = formatDuration(file.duration_seconds)
              return (
                <button
                  key={file.id}
                  onClick={() => {
                    void startTrack(idx)
                    setDialogOpen(false)
                  }}
                  className={`w-full flex items-center justify-between gap-3 px-3 py-2.5 rounded-lg text-sm transition-colors text-left ${
                    isCurrentTrack
                      ? 'bg-orange-500/15 text-orange-400'
                      : 'hover:bg-muted text-foreground'
                  }`}
                >
                  <span className="flex items-center gap-2 min-w-0">
                    {isCurrentTrack && playing ? (
                      <svg className="w-3.5 h-3.5 shrink-0" fill="currentColor" viewBox="0 0 24 24">
                        <rect x="6" y="4" width="4" height="16" rx="1" />
                        <rect x="14" y="4" width="4" height="16" rx="1" />
                      </svg>
                    ) : (
                      <svg
                        className="w-3.5 h-3.5 shrink-0 opacity-50"
                        fill="currentColor"
                        viewBox="0 0 24 24"
                      >
                        <path d="M8 5v14l11-7z" />
                      </svg>
                    )}
                    <span className="truncate">{label}</span>
                  </span>
                  {duration && (
                    <span className="text-xs text-muted-foreground shrink-0 tabular-nums">
                      {duration}
                    </span>
                  )}
                </button>
              )
            })}
          </div>
        </DialogContent>
      </Dialog>
    </div>
  )
}

// ─── Shared helpers ────────────────────────────────────────────────────────────

function MetaRow({ label, value }: { label: string; value: React.ReactNode }) {
  return (
    <div className="flex items-center gap-3">
      <span className="text-neutral-400 text-sm w-28 flex-shrink-0">{label}</span>
      <span className="text-white text-sm">{value}</span>
    </div>
  )
}

export function BuyButton({ price, currency }: { price: number; currency: string }) {
  const { t } = useTranslation()
  return (
    <button className="w-full flex items-center justify-between bg-[#1a2e1a] hover:bg-[#22381a] border border-green-900 rounded-xl px-4 py-3 transition-colors group">
      <div className="flex items-center gap-2">
        <svg
          xmlns="http://www.w3.org/2000/svg"
          className="w-4 h-4 text-green-400"
          fill="none"
          viewBox="0 0 24 24"
          stroke="currentColor"
          strokeWidth={2}
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            d="M3 3h2l.4 2M7 13h10l4-8H5.4M7 13l-1.35 2.7A1 1 0 007 17h11m-5 0a2 2 0 100 4 2 2 0 000-4zm-6 0a2 2 0 100 4 2 2 0 000-4z"
          />
        </svg>
        <span className="text-white font-medium">{t('book.buy')}</span>
      </div>
      <span className="text-lime-400 font-bold text-lg">
        {price} {currency}
      </span>
    </button>
  )
}
