import { BrowserRouter, Routes, Route, Navigate, Outlet } from 'react-router-dom'
import { HomePage, BookPage, ShelfPage, GenrePage, LoginPage } from './pages/index.ts'
import { LeftSidebar, Navbar, MediaPlayer } from './layout/index.ts'
import { MediaPlayerProvider } from './components/media-player/index.ts'
import AuthPrompt from './components/AuthPrompt.tsx'
import { AuthProvider } from './hooks/AuthProvider.tsx'
import PrivateRoute from './components/PrivateRoute.tsx'
import AdminLayout from './layout/AdminLayout.tsx'
import AdminUsersList from './pages/AdminUsersList.tsx'
import AdminBooksList from './pages/AdminBooksList.tsx'
import UserProfile from './pages/UserProfile.tsx'
import PublisherPage from './pages/PublisherPage.tsx'
import AuthorPage from './pages/AuthorPage.tsx'
import SearchPage from './pages/SearchPage.tsx'
import { SidebarProvider, useSidebar } from './components/ui/sidebar.tsx'
import AppSidebar from './layout/AppSidebar.tsx'
import { useEffect } from 'react'
import { useTranslation } from 'react-i18next'
import AdminBookFormPage from '@/pages/AdminBookFormPage.tsx'
import AdminUserFormPage from '@/pages/AdminUserFormPage.tsx'
import AdminBookPage from '@/pages/AdminBookPage.tsx'
import AdminUserPage from '@/pages/AdminUserPage.tsx'
import AdminApiTokensPage from '@/pages/AdminApiTokensPage.tsx'
import { Toaster } from 'sonner'
import TermsPage from './pages/TermsPage.tsx'

function AppLayoutContent() {
  const { i18n } = useTranslation()
  const { state } = useSidebar()
  const contentDir = i18n.language === 'ar' ? 'rtl' : 'ltr'

  // Update CSS variable for media player adjustment
  useEffect(() => {
    const sidebarWidth = state === 'expanded' ? '260px' : '0px'
    document.documentElement.style.setProperty('--right-sidebar-width', sidebarWidth)
  }, [state])

  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100vh', width: '100%' }}>
      <Navbar />
      <div style={{ display: 'flex', flex: 1, overflow: 'hidden' }} dir="ltr">
        <LeftSidebar />
        <main
          dir={contentDir}
          style={{ flex: 1, overflowY: 'auto', padding: '24px 32px', paddingBottom: '66px' }}
        >
          <Outlet />
        </main>
        <AppSidebar />
      </div>
      <MediaPlayer />
      <AuthPrompt />
    </div>
  )
}

function AppLayout() {
  return (
    <SidebarProvider
      defaultOpen={false}
      style={{ '--sidebar-width': '260px' } as React.CSSProperties}
    >
      <AppLayoutContent />
    </SidebarProvider>
  )
}

// todo: currently that violates the design but it's ok for a transition period
export default function App() {
  return (
    <AuthProvider>
      <Toaster position="bottom-right" richColors closeButton />
      <BrowserRouter>
        <MediaPlayerProvider>
          <Routes>
            <Route path="/login" element={<LoginPage />} />
            <Route path="/terms" element={<TermsPage />} />
            <Route element={<PrivateRoute />}>
              <Route element={<AppLayout />}>
                <Route path="/" element={<HomePage />} />
                <Route path="/search" element={<SearchPage />} />
                <Route path="/users/:userId" element={<UserProfile />} />
                <Route path="/author/:authorId" element={<AuthorPage />} />
                <Route path="/publisher/:publisherId" element={<PublisherPage />} />
                <Route path="/book/:bookId" element={<BookPage />} />
                <Route path="/shelf" element={<ShelfPage />} />
                <Route path="/genre/:genreId" element={<GenrePage />} />
                <Route path="*" element={<Navigate to="/" replace />} />
              </Route>
              <Route path="/admin" element={<AdminLayout />}>
                <Route index element={<AdminUsersList />} />
                <Route path="/admin/books" element={<AdminBooksList />} />
                <Route path="/admin/books/new" element={<AdminBookFormPage />} />
                <Route path="/admin/books/:bookId" element={<AdminBookPage />} />
                <Route path="/admin/api-tokens" element={<AdminApiTokensPage />} />
                <Route path="/admin/users/:userId" element={<AdminUserPage />} />
                <Route path="/admin/users/new" element={<AdminUserFormPage />} />
              </Route>
            </Route>
          </Routes>
        </MediaPlayerProvider>
      </BrowserRouter>
    </AuthProvider>
  )
}
