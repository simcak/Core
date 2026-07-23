import { useEffect, useState } from 'react'
import { Link, useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { useAuth } from '../hooks/useAuth.ts'
import type { LoginResponse } from '../types/auth.ts'
import { Button } from '../components/ui/button.tsx'
import { Input } from '../components/ui/input.tsx'
import { Label } from '../components/ui/label.tsx'
import { authUrl } from '../utils/auth.ts'

export default function LoginPage() {
  const { t } = useTranslation()
  const [showRegister, setShowRegister] = useState(false)
  const [registerLoading, setRegisterLoading] = useState(false)
  const [registerError, setRegisterError] = useState('')
  const [registerSuccess, setRegisterSuccess] = useState('')
  const [loginLoading, setLoginLoading] = useState(false)
  const [loginError, setLoginError] = useState('')
  const navigate = useNavigate()
  const { token, loading, login } = useAuth()

  const REGISTER_URL = authUrl(`/auth/register`)
  const LOGIN_URL = authUrl(`/auth/login`)
  const OAUTH_URL = authUrl(`/auth/42`)
  const GOOGLE_OAUTH_URL = authUrl(`/auth/google`)

  useEffect(() => {
    if (!loading && token) {
      navigate('/', { replace: true })
    }
  }, [loading, navigate, token])

  function loginWith42() {
    window.location.assign(OAUTH_URL)
  }

  function loginWithGoogle() {
    window.location.assign(GOOGLE_OAUTH_URL)
  }

  const handleSubmit = async (event: {
    preventDefault(): void
    currentTarget: HTMLFormElement
  }) => {
    event.preventDefault()

    const formData = new FormData(event.currentTarget)
    const email = String(formData.get('email') ?? '').trim()
    const password = String(formData.get('password') ?? '')

    setLoginLoading(true)
    setLoginError('')
    setRegisterSuccess('')

    try {
      const response = await fetch(LOGIN_URL, {
        method: 'POST',
        credentials: 'include',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password }),
      })

      if (!response.ok) {
        const errorBody = await response.json().catch(() => ({}))
        const detail =
          typeof errorBody.detail === 'string' ? errorBody.detail : t('auth.loginFailed')
        setLoginError(detail)
        setRegisterSuccess('')
        return
      }
      const data = (await response.json()) as LoginResponse
      login(data.user, data.access_token)
      navigate('/')
    } catch (e) {
      console.log(e)
      setLoginError(t('auth.loginFailed'))
      setRegisterSuccess('')
    } finally {
      setLoginLoading(false)
    }
  }

  const handleRegister = async (event: {
    preventDefault(): void
    currentTarget: HTMLFormElement
  }) => {
    event.preventDefault()

    const formData = new FormData(event.currentTarget)
    const username = String(formData.get('username') ?? '').trim()
    const firstName = String(formData.get('firstName') ?? '').trim()
    const lastName = String(formData.get('lastName') ?? '').trim()
    const phone = String(formData.get('phone') ?? '').trim()
    const email = String(formData.get('registerEmail') ?? '').trim()
    const password = String(formData.get('registerPassword') ?? '')
    const confirm = String(formData.get('registerPasswordConfirm') ?? '')

    if (password !== confirm) {
      setRegisterError(t('auth.passwordsNoMatch'))
      setRegisterSuccess('')
      setLoginError('')
      return
    }

    setRegisterLoading(true)
    setRegisterError('')
    setRegisterSuccess('')
    setLoginError('')

    try {
      const response = await fetch(REGISTER_URL, {
        method: 'POST',
        credentials: 'include',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          email,
          password,
          username,
          first_name: firstName || undefined,
          last_name: lastName || undefined,
          phone: phone || undefined,
        }),
      })

      if (!response.ok) {
        const errorBody = await response.json().catch(() => ({}))
        const detail =
          typeof errorBody.detail === 'string' ? errorBody.detail : t('auth.registrationFailed')
        setRegisterError(detail)
        setLoginError('')
        return
      }

      setRegisterSuccess(t('auth.accountCreated'))
      setLoginError('')
      setShowRegister(false)
      ;(event.currentTarget as HTMLFormElement).reset()
    } catch {
      setRegisterError(t('auth.registrationFailed'))
    } finally {
      setRegisterLoading(false)
    }
  }
  return (
    <div className="login-page">
      <div className="login-shell">
        <section className="login-card">
          <div className="login-card-header">
            <h2>{showRegister ? t('auth.createAccount') : t('auth.welcomeBack')}</h2>
          </div>

          {registerSuccess && !showRegister && !loginError && (
            <p className="login-alert login-alert-success">{registerSuccess}</p>
          )}

          {!showRegister && (
            <form className="login-form" onSubmit={handleSubmit}>
              {loginError && !registerSuccess && (
                <p className="login-alert login-alert-error">{loginError}</p>
              )}
              <div className="flex flex-col gap-2">
                <Label htmlFor="login-email">{t('auth.email')}</Label>
                <Input
                  id="login-email"
                  type="email"
                  name="email"
                  placeholder={t('auth.emailPlaceholder')}
                  required
                />
              </div>

              <div className="flex flex-col gap-2">
                <Label htmlFor="login-password">{t('auth.password')}</Label>
                <Input
                  id="login-password"
                  type="password"
                  name="password"
                  placeholder={t('auth.enterPassword')}
                  required
                />
              </div>

              <div className="login-row">


              </div>

              <Button className="login-submit" type="submit">
                {loginLoading ? t('auth.signingIn') : t('auth.signIn')}
              </Button>
              <Button
                className="login-submit"
                variant="outline"
                type="button"
                onClick={loginWith42}
              >
                {t('auth.signInWith42')}
              </Button>
              <Button
                className="login-submit"
                variant="outline"
                type="button"
                onClick={loginWithGoogle}
              >
                Sign in with Google
              </Button>

              <Button
                className="login-outline"
                variant="outline"
                type="button"
                onClick={() => setShowRegister(true)}
              >
                {t('auth.register')}
              </Button>

              <p className="login-footer">
                {t('auth.legalPrompt')}{' '}
                <Link to="/terms" className="login-footer-link">
                  {t('auth.termsLink')}
                </Link>
              </p>
            </form>
          )}

          {showRegister && (
            <form className="login-form login-register" onSubmit={handleRegister}>
              {registerError && <p className="login-alert login-alert-error">{registerError}</p>}
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-username">{t('auth.username')}</Label>
                <Input
                  id="register-username"
                  type="text"
                  name="username"
                  placeholder={t('auth.chooseUsername')}
                  required
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-email">{t('auth.email')}</Label>
                <Input
                  id="register-email"
                  type="email"
                  name="registerEmail"
                  placeholder={t('auth.emailPlaceholder')}
                  required
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-first-name">{t('auth.firstName')}</Label>
                <Input
                  id="register-first-name"
                  type="text"
                  name="firstName"
                  placeholder={t('auth.optional')}
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-last-name">{t('auth.lastName')}</Label>
                <Input
                  id="register-last-name"
                  type="text"
                  name="lastName"
                  placeholder={t('auth.optional')}
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-phone">{t('auth.phone')}</Label>
                <Input
                  id="register-phone"
                  type="tel"
                  name="phone"
                  placeholder={t('auth.optional')}
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-password">{t('auth.password')}</Label>
                <Input
                  id="register-password"
                  type="password"
                  name="registerPassword"
                  placeholder={t('auth.createPassword')}
                  required
                />
              </div>
              <div className="flex flex-col gap-2">
                <Label htmlFor="register-password-confirm">{t('auth.confirmPassword')}</Label>
                <Input
                  id="register-password-confirm"
                  type="password"
                  name="registerPasswordConfirm"
                  placeholder={t('auth.repeatPassword')}
                  required
                />
              </div>

              <p className="login-footer">
                {t('auth.createAccountLegalPrefix')}{' '}
                <Link to="/terms" className="login-footer-link">
                  {t('auth.termsLink')}
                </Link>
                .
              </p>

              <Button className="login-submit" type="submit">
                {registerLoading ? t('auth.creatingAccount') : t('auth.createAccountBtn')}
              </Button>

              <Button
                className="login-outline"
                variant="outline"
                type="button"
                onClick={() => setShowRegister(false)}
              >
                {t('auth.backToSignIn')}
              </Button>
            </form>
          )}
        </section>
      </div>
    </div>
  )
}
