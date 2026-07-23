import { createContext, useContext } from 'react'
import type { TrackInfo, Chapter } from './types'

// A single audio file from the backend (one chapter = one file)
export interface AudioFile {
  id: number
  title: string // derived from original_filename
  mimeType: string
  durationSeconds: number | null
}

export interface AudioContextValue {
  track: TrackInfo | null
  files: AudioFile[]
  currentFileIdx: number
  audioSrc: { src: string; type: string } | null
  isLoading: boolean
  // True only while audio is actively playing (paused → false, stopped → false)
  playing: boolean
  // Resume paused playback without re-loading the track
  resumePlayback: () => void
  // Internal: called by the MediaPlayer subtree to wire up vidstack state/controls
  onPlayingChange: (playing: boolean) => void
  registerResume: (fn: () => void) => void
  // Load a book by id — fetches the file list, builds chapters, starts playing
  loadBook: (
    bookId: number,
    meta: { title: string; author: string; coverUrl?: string | null },
    startFileIdx?: number
  ) => Promise<void>
  // Jump to a specific file by index
  goToFile: (idx: number) => void
  // Advance to next file (called on track end)
  advance: () => void
  dismiss: () => void
}

export { type TrackInfo, type Chapter }

export const AudioContext = createContext<AudioContextValue | null>(null)

export function useAudioContext(): AudioContextValue {
  const ctx = useContext(AudioContext)
  if (!ctx) throw new Error('useAudioContext must be used inside <MediaPlayerProvider>')
  return ctx
}
