import { useTranslation } from 'react-i18next'
import BookList from '../lists/BookList'
import type { ShortBook } from '../book/types'

interface ShelfBooksSectionProps {
  books: ShortBook[]
  loading: boolean
  accentColor: string
}

export default function ShelfBooksSection({ books, loading, accentColor }: ShelfBooksSectionProps) {
  const { t } = useTranslation()
  return (
    <BookList
      sectionName={t('shelf.myBooks')}
      books={books}
      loading={loading}
      layout="grid"
      accentColor={accentColor}
      showPrice={false}
      emptyMessage={t('shelf.empty')}
    />
  )
}
