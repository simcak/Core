import { useEffect, useState } from 'react'
import { Link, useLocation } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { AUTH_REQUIRED_EVENT, isLoggedIn } from '../utils/auth'

export default function AuthPrompt() {
  const { t } = useTranslation()
  const location = useLocation()
  const [loggedIn, setLoggedIn] = useState(() => isLoggedIn())
  const [isOpen, setIsOpen] = useState(location.pathname === '/login')
  // REDIRECT TO LOGIN
  useEffect(() => {
    const handleStorage = () => setLoggedIn(isLoggedIn())
    const handleAuthRequired = () => {
      if (!isLoggedIn() && location.pathname !== '/login') {
        setIsOpen(true)
      }
    }

    window.addEventListener('storage', handleStorage)
    window.addEventListener(AUTH_REQUIRED_EVENT, handleAuthRequired)
    return () => {
      window.removeEventListener('storage', handleStorage)
      window.removeEventListener(AUTH_REQUIRED_EVENT, handleAuthRequired)
    }
  }, [location.pathname])

  if (location.pathname === '/login' || loggedIn || !isOpen) {
    return null
  }

  return (
    <div className="auth-prompt-overlay" role="dialog" aria-modal="true">
      <div className="auth-prompt-card">
        <p className="auth-prompt-title">{t('authPrompt.title')}</p>
        <p className="auth-prompt-body">{t('authPrompt.body')}</p>
        <div className="auth-prompt-actions">
          <Link
            className="auth-prompt-btn auth-prompt-primary"
            to="/login"
            onClick={() => setIsOpen(false)}
          >
            {t('authPrompt.goToLogin')}
          </Link>
          <button
            type="button"
            className="auth-prompt-btn auth-prompt-ghost"
            onClick={() => setIsOpen(false)}
          >
            {t('authPrompt.maybeLater')}
          </button>
        </div>
      </div>
    </div>
  )
}
