import { Link } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import DiscoverSection from '../components/home/DiscoverSection.tsx'
import GenresSection from '../components/home/GenresSection.tsx'
import BestSellersSection from '../components/home/BestSellersSection.tsx'

export default function HomePage() {
  const { t } = useTranslation()

  return (
    <>
      <DiscoverSection />
      <GenresSection />
      <BestSellersSection />
      <footer className="home-footer">
        <span>{t('home.footerInfo')}</span>
        <Link to="/terms" className="home-footer-link">
          {t('auth.termsLink')}
        </Link>
      </footer>
    </>
  )
}
