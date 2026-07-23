import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import '@vidstack/react/player/styles/base.css'
import './index.css'
import './i18n.ts'
import App from './App.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <App />
  </StrictMode>
)
