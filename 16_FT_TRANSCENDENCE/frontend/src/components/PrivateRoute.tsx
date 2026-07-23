import { Navigate, Outlet } from 'react-router-dom'
import { useAuth } from '../hooks/useAuth.ts'

export default function PrivateRoute() {
  const { token, loading } = useAuth()
  if (loading) return null

  return token ? <Outlet /> : <Navigate to="/login" replace />
}
