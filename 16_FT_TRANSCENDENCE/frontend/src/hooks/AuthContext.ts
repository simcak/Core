import { createContext } from 'react'
import type { User } from '../types/auth.ts'

interface AuthContextType {
  user: User | null
  token: string | null
  loading: boolean
  login: (user: User, token: string) => void
  logout: () => void
}

export const AuthContext = createContext<AuthContextType | null>(null)
