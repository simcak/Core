export const AUTH_TOKEN_KEY = 'access_token'
export const AUTH_USER_KEY = 'authUser'
export const AUTH_REQUIRED_EVENT = 'auth:required'
export const AUTH_CHANGED_EVENT = 'auth:changed'
export const AUTH_API_BASE_URL = import.meta.env.VITE_AUTH_API_URL ?? ''
export const authUrl = (path: string) => `${AUTH_API_BASE_URL}${path}`

// todo: removal. Use AuthContext instead
export const isLoggedIn = () =>
  Boolean(localStorage.getItem(AUTH_TOKEN_KEY) || localStorage.getItem(AUTH_USER_KEY))

export const requestLogin = () => {
  window.dispatchEvent(new Event(AUTH_REQUIRED_EVENT))
}

export const getStoredUser = <T = unknown>() => {
  const raw = localStorage.getItem(AUTH_USER_KEY)
  if (!raw) return null
  try {
    return JSON.parse(raw) as T
  } catch {
    return null
  }
}
