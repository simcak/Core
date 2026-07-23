import { useTranslation } from 'react-i18next'
import BookList from '../lists/BookList'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

interface GenreBooksSectionProps {
  categoryId: number
  color: string
}

export default function GenreBooksSection({ categoryId, color }: GenreBooksSectionProps) {
  const { t } = useTranslation()
  return (
    <BookList
      sectionName={t('genre.books')}
      fetchUrl={`${API_URL}/books?category_id=${categoryId}&status=active`}
      layout="grid"
      accentColor={color}
      imageSize={160}
    />
  )
}
