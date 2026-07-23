import { useTranslation } from 'react-i18next'
import { Button } from '../ui/button'

export default function Subscription() {
  const { t } = useTranslation()
  return (
    <div className="bg-white/7 border border-white/10 rounded-lg p-4 mb-4">
      <h2 className="m-0 text-sm">{t('subscription.title')}</h2>
      <p className="m-0 text-sm text-white/60 mt-2">
        {t('subscription.currentPlan')} <strong>{t('subscription.freePlan')}</strong>.{' '}
        {t('subscription.upgradeDesc')}
      </p>
      <Button className="mt-4">{t('subscription.upgradeNow')}</Button>
    </div>
  )
}
