interface StarRatingProps {
  value: number | null
  onChange?: (v: number) => void
  readOnly?: boolean
  size?: 'sm' | 'md' | 'lg'
}

const sizeClass = { sm: 'text-base', md: 'text-xl', lg: 'text-3xl' }

export default function StarRating({
  value,
  onChange,
  readOnly = false,
  size = 'md',
}: StarRatingProps) {
  return (
    <div className="flex gap-0.5">
      {[1, 2, 3, 4, 5].map((star) => (
        <button
          key={star}
          type="button"
          disabled={readOnly}
          onClick={() => onChange?.(star)}
          className={[
            sizeClass[size],
            readOnly ? 'cursor-default' : 'cursor-pointer hover:scale-110 transition-transform',
            (value ?? 0) >= star ? 'text-yellow-400' : 'text-neutral-600',
          ].join(' ')}
        >
          ★
        </button>
      ))}
    </div>
  )
}
