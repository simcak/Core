import { useTranslation } from 'react-i18next'
import { useAuth } from '../../hooks/useAuth.ts'
import { Button } from '../ui/button.tsx'

export default function LogOut() {
  const { t } = useTranslation()
  const { logout } = useAuth()
  return (
    <Button onClick={logout} variant="destructive" className="w-full">
      {t('logOut')}
    </Button>
  )
}
