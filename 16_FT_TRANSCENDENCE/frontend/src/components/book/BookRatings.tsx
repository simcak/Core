import { useState, useEffect, useCallback } from 'react'
import { Link } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import type { BookReviewsData } from './types'
import { useAuth } from '@/hooks/useAuth.ts'
import StarRating from '../common/StarRating'
import ReviewForm from './ReviewForm'
import { Button } from '../ui/button'
import { UserAvatar } from '../ui/avatar'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface BookRatingsProps {
  bookId: number
}

export default function BookRatings({ bookId }: BookRatingsProps) {
  const { t } = useTranslation()
  const { user } = useAuth()
  const [data, setData] = useState<BookReviewsData | null>(null)
  const [formOpen, setFormOpen] = useState(false)

  const load = useCallback(() => {
    fetch(`${API_URL}/books/${bookId}/reviews`, { credentials: 'include' })
      .then((r) => (r.ok ? r.json() : null))
      .then(setData)
  }, [bookId])

  useEffect(() => {
    load()
  }, [load])

  const userHasReview =
    user != null && (data?.reviews.some((r) => r.username === user.username) ?? false)
  const reviews = data?.reviews ?? []

  return (
    <div className="flex flex-col gap-4">
      <div className="flex items-center justify-between">
        <div className="flex items-center gap-3">
          <h2 className="text-xl font-semibold text-white">{t('book.ratings')}</h2>
          {data?.average_rating != null && (
            <div className="flex items-center gap-1.5">
              <span className="text-yellow-400 text-lg">★</span>
              <span className="text-white font-semibold text-lg">{data.average_rating}</span>
              <span className="text-neutral-500 text-sm">({data.count})</span>
            </div>
          )}
          {data?.count === 0 && (
            <span className="text-neutral-500 text-sm">{t('book.noRatings')}</span>
          )}
        </div>
        {user && !userHasReview && (
          <Button variant="outline" size="sm" onClick={() => setFormOpen(true)}>
            {t('book.writeReview')}
          </Button>
        )}
      </div>

      {reviews.length > 0 && (
        <div className="flex flex-col gap-3 max-h-105 overflow-y-auto pr-1 scrollbar-thin scrollbar-thumb-neutral-700 scrollbar-track-transparent">
          {reviews.map((review) => (
            <div
              key={review.id}
              className="bg-[#1a1a1a] border border-neutral-800 rounded-2xl p-4 flex flex-col gap-2"
            >
              <div className="flex items-center gap-3">
                <Link
                  to={`/users/${review.user_id}`}
                  className="flex items-center gap-2.5 group min-w-0"
                >
                  <UserAvatar
                    src={`${API_URL}/auth/users/${review.user_id}/avatar`}
                    name={review.username}
                    size="lg"
                  />
                  <span className="text-white font-medium text-sm group-hover:text-orange-400 transition-colors truncate">
                    {review.username}
                  </span>
                </Link>
                <div className="ml-auto shrink-0">
                  <StarRating value={review.rating} readOnly size="sm" />
                </div>
              </div>
              {review.text && (
                <p className="text-neutral-300 text-sm leading-relaxed">{review.text}</p>
              )}
            </div>
          ))}
        </div>
      )}

      {user && formOpen && (
        <ReviewForm
          bookId={bookId}
          username={user.username}
          open={formOpen}
          onClose={() => setFormOpen(false)}
          onSubmitted={() => {
            load()
          }}
        />
      )}
    </div>
  )
}
