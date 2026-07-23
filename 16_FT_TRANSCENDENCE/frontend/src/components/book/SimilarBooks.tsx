import { useTranslation } from 'react-i18next'
import BookList from '../lists/BookList'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface SimilarBooksProps {
  bookId: string
}

export default function SimilarBooks({ bookId }: SimilarBooksProps) {
  const { t } = useTranslation()
  console.log(bookId)
  return (
    <BookList
      sectionName={t('book.similar')}
      // fetchUrl={`${API_URL}/books/${bookId}/similar`}. // swap for real endpoint
      fetchUrl={`${API_URL}/books?status=active`}
      layout="scroll"
    />
  )
}
