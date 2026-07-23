import { useContext } from 'react'
import { AuthContext } from './AuthContext.ts'

export const useAuth = () => {
  const context = useContext(AuthContext)
  if (!context) throw new Error('useAuth must be used within an AuthProvider')
  const { user, token, loading, login, logout } = context
  const isAuthorized = (requiredRole: string) => {
    return user && user.role.role_name === requiredRole
  }
  return { user, token, loading, login, logout, isAuthorized }
}
