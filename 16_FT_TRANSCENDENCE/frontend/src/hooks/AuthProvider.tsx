import React, { useEffect, useState } from 'react'
import { AUTH_CHANGED_EVENT, AUTH_TOKEN_KEY, AUTH_USER_KEY, authUrl } from '../utils/auth.ts'
import type { User } from '../types/auth.ts'
import { AuthContext } from './AuthContext.ts'

interface AuthProviderProps {
  children: React.ReactNode
}

const COOKIE_SESSION_TOKEN = 'cookie-session'
const ME_URL = authUrl('/auth/me')
const LOGOUT_URL = authUrl('/auth/logout')
const HEARTBEAT_URL = authUrl('/auth/heartbeat')
const HEARTBEAT_INTERVAL_MS = 42000

export const AuthProvider = ({ children }: AuthProviderProps) => {
  const [user, setUser] = useState(() => {
    const storedUser = localStorage.getItem(AUTH_USER_KEY)
    return storedUser ? JSON.parse(storedUser) : null
  })

  const [token, setToken] = useState<string | null>(() => {
    return localStorage.getItem(AUTH_TOKEN_KEY)
  })
  const [loading, setLoading] = useState(true)

  useEffect(() => {
    let mounted = true

    const clearAuth = () => {
      setUser(null)
      setToken(null)
      localStorage.removeItem(AUTH_USER_KEY)
      localStorage.removeItem(AUTH_TOKEN_KEY)
    }

    const loadSession = async () => {
      try {
        const response = await fetch(ME_URL, { credentials: 'include' })
        if (!mounted) return

        if (!response.ok) {
          clearAuth()
          return
        }

        const currentUser = (await response.json()) as User
        const storedToken = localStorage.getItem(AUTH_TOKEN_KEY)
        setUser(currentUser)
        setToken(storedToken || COOKIE_SESSION_TOKEN)
        localStorage.setItem(AUTH_USER_KEY, JSON.stringify(currentUser))
        window.dispatchEvent(new Event(AUTH_CHANGED_EVENT))
      } catch {
        if (mounted) {
          clearAuth()
        }
      } finally {
        if (mounted) {
          setLoading(false)
        }
      }
    }

    void loadSession()

    return () => {
      mounted = false
    }
  }, [])

  useEffect(() => {
    if (!token) {
      return
    }

    const sendHeartbeat = () => {
      void fetch(HEARTBEAT_URL, { method: 'POST', credentials: 'include' })
    }

    sendHeartbeat()
    const intervalId = window.setInterval(sendHeartbeat, HEARTBEAT_INTERVAL_MS)

    return () => {
      window.clearInterval(intervalId)
    }
  }, [token])

  const login = (userData: User, token: string) => {
    setUser(userData)
    setToken(token)
    localStorage.setItem(AUTH_USER_KEY, JSON.stringify(userData))
    localStorage.setItem(AUTH_TOKEN_KEY, token)
    window.dispatchEvent(new Event(AUTH_CHANGED_EVENT))
  }

  const logout = () => {
    void fetch(LOGOUT_URL, {
      method: 'POST',
      credentials: 'include',
    })
    setUser(null)
    setToken(null)
    localStorage.removeItem(AUTH_USER_KEY)
    localStorage.removeItem(AUTH_TOKEN_KEY)
    window.dispatchEvent(new Event(AUTH_CHANGED_EVENT))
  }

  return (
    <AuthContext.Provider value={{ user, token, loading, login, logout }}>
      {children}
    </AuthContext.Provider>
  )
}
