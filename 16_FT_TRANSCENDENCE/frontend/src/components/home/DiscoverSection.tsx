import { useTranslation } from 'react-i18next'
import BookList from '../lists/BookList'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

export default function DiscoverSection() {
  const { t } = useTranslation()
  return (
    <BookList
      sectionName={t('home.discover')}
      fetchUrl={`${API_URL}/books?status=active`}
      layout="scroll"
      imageSize={190}
    />
  )
}
