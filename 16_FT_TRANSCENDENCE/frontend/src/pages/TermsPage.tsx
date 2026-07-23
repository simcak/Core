import { Link } from 'react-router-dom'
import { useTranslation } from 'react-i18next'

const UPDATED_DATE = new Date('2026-06-19')
const CONTACT_EMAIL = 'info@berryaudio.com'

export default function TermsPage() {
  const { t, i18n } = useTranslation()
  const formattedDate = new Intl.DateTimeFormat(i18n.language, {
    year: 'numeric',
    month: 'long',
    day: 'numeric',
  }).format(UPDATED_DATE)

  return (
    <main className="terms-page">
      <article className="terms-document">
        <Link to="/login" className="terms-back-link">
          {t('legal.backToLogin')}
        </Link>

        <header className="terms-header">
          <p>{t('legal.updated', { date: formattedDate })}</p>
          <h1>{t('legal.mainTitle')}</h1>
        </header>

        <section>
          <h2>{t('legal.termsTitle')}</h2>
          <p>{t('legal.termsBody')}</p>
        </section>

        <section>
          <h2>{t('legal.accountsTitle')}</h2>
          <p>{t('legal.accountsBody')}</p>
        </section>

        <section>
          <h2>{t('legal.privacyTitle')}</h2>
          <p>{t('legal.privacyBody')}</p>
        </section>

        <section>
          <h2>{t('legal.dataTitle')}</h2>
          <p>{t('legal.dataBody')}</p>
        </section>

        <section>
          <h2 className="terms-contact-heading">
            <span>{t('legal.contactTitle')}</span>
            <a href={`mailto:${CONTACT_EMAIL}`}>{CONTACT_EMAIL}</a>
          </h2>
          <p>{t('legal.contactBody')}</p>
        </section>
      </article>
    </main>
  )
}
