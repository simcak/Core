import { Outlet, useNavigate } from 'react-router-dom'
import { useState } from 'react'
import { useTranslation } from 'react-i18next'
import logo from '../assets/logo-white.png'
import LogOut from '../components/settings/LogOut.tsx'

export default function AdminLayout() {
  const { t } = useTranslation()
  const navigate = useNavigate()
  const [sidebarOpen, setSidebarOpen] = useState(true)
  /*
	//review this later, put in in the logout component
  const handleLogout = () => {
    // Clear auth data
    localStorage.removeItem('token')
    navigate('/login')
  }
*/
  const navItems = [
    { label: t('admin.manageUsers'), path: '/admin/', isBack: false },
    { label: t('admin.manageBooks'), path: '/admin/books', isBack: false },
    { label: t('admin.manageApiTokens'), path: '/admin/api-tokens', isBack: false },
    //	{ label: 'Manage Settings', path: '/admin/settings' },
    { label: t('admin.backToApp'), path: '/', isBack: true },
  ]

  return (
    <div
      style={{
        display: 'flex',
        height: '100vh',
        background: '#0f172a',
        color: 'rgba(255,255,255,0.95)',
      }}
    >
      {/* Sidebar */}
      <aside
        style={{
          width: sidebarOpen ? 280 : 0,
          background: 'rgba(15,23,42,0.8)',
          borderRight: '1px solid rgba(148,163,184,0.15)',
          display: 'flex',
          flexDirection: 'column',
          transition: 'width 300ms ease',
          overflow: 'hidden',
        }}
      >
        {/* Logo */}
        <div
          style={{
            padding: '24px 20px',
            borderBottom: '1px solid rgba(148,163,184,0.15)',
            minHeight: 64,
            display: 'flex',
            flexDirection: 'column',
            alignItems: 'center',
            gap: 12,
          }}
        >
          <img
            src={logo}
            alt="App Logo"
            style={{
              width: 120,
              height: 'auto',
              objectFit: 'contain',
            }}
          />

          <h2
            style={{
              fontSize: 18,
              fontWeight: 700,
              color: '#60a5fa',
              letterSpacing: '-0.5px',
              margin: 0,
            }}
          >
            {t('admin.panel')}
          </h2>
        </div>

        {/* Navigation */}
        <nav
          style={{
            flex: 1,
            padding: '20px 12px',
            display: 'flex',
            flexDirection: 'column',
            gap: 8,
          }}
        >
          {navItems.map((item) => (
            <button
              key={item.path}
              onClick={() => navigate(item.path)}
              style={{
                width: '100%',
                padding: '12px 16px',
                background: 'transparent',
                border: 'none',
                borderRadius: 6,
                color: item.isBack ? 'rgba(255,255,255,0.55)' : 'rgba(255,255,255,0.75)',
                textAlign: 'left',
                fontSize: 14,
                fontWeight: 500,
                cursor: 'pointer',
                transition: 'all 200ms',
                borderLeft: '3px solid transparent',
              }}
              onMouseEnter={(e) => {
                e.currentTarget.style.background = 'rgba(96,165,250,0.1)'
                e.currentTarget.style.borderLeftColor = '#60a5fa'
                e.currentTarget.style.color = '#60a5fa'
              }}
              onMouseLeave={(e) => {
                e.currentTarget.style.background = 'transparent'
                e.currentTarget.style.borderLeftColor = 'transparent'
                e.currentTarget.style.color = item.isBack
                  ? 'rgba(255,255,255,0.55)'
                  : 'rgba(255,255,255,0.75)'
              }}
            >
              {item.label}
            </button>
          ))}
        </nav>

        {/* Logout */}
        <div
          style={{
            padding: '12px',
            borderTop: '1px solid rgba(148,163,184,0.15)',
          }}
        >
          <LogOut />
        </div>
      </aside>

      {/* Main Content */}
      <div
        style={{
          flex: 1,
          display: 'flex',
          flexDirection: 'column',
        }}
      >
        {/* Top Bar */}
        <header
          style={{
            height: 64,
            background: 'rgba(15,23,42,0.7)',
            borderBottom: '1px solid rgba(148,163,184,0.15)',
            display: 'flex',
            alignItems: 'center',
            paddingLeft: 20,
            paddingRight: 32,
          }}
        >
          <button
            onClick={() => setSidebarOpen(!sidebarOpen)}
            style={{
              background: 'none',
              border: 'none',
              color: 'rgba(255,255,255,0.65)',
              cursor: 'pointer',
              display: 'flex',
              alignItems: 'center',
              padding: '8px',
              transition: 'color 200ms',
              fontSize: 20,
              fontWeight: 600,
            }}
            onMouseEnter={(e) => (e.currentTarget.style.color = '#60a5fa')}
            onMouseLeave={(e) => (e.currentTarget.style.color = 'rgba(255,255,255,0.65)')}
          >
            ☰
          </button>
        </header>

        {/* Page Content */}
        <main
          style={{
            flex: 1,
            overflowY: 'auto',
            padding: '32px',
            background: '#0f172a',
          }}
        >
          <Outlet /> {/* ← This is where AdminUsersList renders */}
        </main>
      </div>
    </div>
  )
}
