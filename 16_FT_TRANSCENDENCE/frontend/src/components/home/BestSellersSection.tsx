import { useTranslation } from 'react-i18next'
import BookList from '../lists/BookList'

const API_URL = import.meta.env.VITE_API_URL ?? '/api'

export default function BestSellersSection() {
  const { t } = useTranslation()
  return (
    <BookList
      sectionName={t('home.bestSellers')}
      fetchUrl={`${API_URL}/books?status=active`} // swap for real endpoint
      layout="scroll"
      imageSize={190}
    />
  )
}
