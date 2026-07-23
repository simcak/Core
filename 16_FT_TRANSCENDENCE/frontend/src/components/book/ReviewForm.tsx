import { useState } from 'react'
import { useTranslation } from 'react-i18next'
import { Dialog, DialogContent, DialogHeader, DialogTitle, DialogFooter } from '../ui/dialog'
import { Button } from '../ui/button'
import { Textarea } from '../ui/textarea'
import StarRating from '../common/StarRating'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface ReviewFormProps {
  bookId: number
  username: string
  open: boolean
  onClose: () => void
  onSubmitted: () => void
}

export default function ReviewForm({
  bookId,
  username,
  open,
  onClose,
  onSubmitted,
}: ReviewFormProps) {
  const { t } = useTranslation()
  const [rating, setRating] = useState<number | null>(null)
  const [text, setText] = useState('')
  const [error, setError] = useState<string | null>(null)
  const [submitting, setSubmitting] = useState(false)

  async function handleSubmit() {
    if (!rating) {
      setError(t('review.selectRating'))
      return
    }
    setSubmitting(true)
    setError(null)
    const res = await fetch(`${API_URL}/books/${bookId}/reviews`, {
      method: 'POST',
      credentials: 'include',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, rating, text: text.trim() || null }),
    })
    setSubmitting(false)
    if (res.ok) {
      onSubmitted()
      onClose()
    } else {
      const data = await res.json().catch(() => ({}))
      setError(data.detail ?? t('review.failed'))
    }
  }

  return (
    <Dialog open={open} onOpenChange={(v) => !v && onClose()}>
      <DialogContent className="bg-[#111] border-neutral-800 text-white max-w-md">
        <DialogHeader>
          <DialogTitle>{t('review.title')}</DialogTitle>
        </DialogHeader>
        <div className="flex flex-col gap-4 py-2">
          <div>
            <p className="text-sm text-neutral-400 mb-2">{t('review.yourRating')}</p>
            <StarRating value={rating} onChange={setRating} size="lg" />
          </div>
          <div>
            <p className="text-sm text-neutral-400 mb-2">{t('review.comment')}</p>
            <Textarea
              value={text}
              onChange={(e) => setText(e.target.value)}
              placeholder={t('review.placeholder')}
              className="bg-[#1a1a1a] border-neutral-700 text-white resize-none"
              rows={4}
              maxLength={1000}
            />
          </div>
          {error && <p className="text-red-400 text-sm">{error}</p>}
        </div>
        <DialogFooter>
          <Button variant="ghost" onClick={onClose} disabled={submitting}>
            {t('review.cancel')}
          </Button>
          <Button onClick={handleSubmit} disabled={submitting || !rating}>
            {submitting ? t('review.submitting') : t('review.submit')}
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
