import { useState, useCallback, useRef } from 'react'
import type { TrackInfo, Chapter } from './types'
import type { AudioFile } from './MPContextDef'
import { AudioContext } from './MPContextDef'
import { setPlayIntent } from './playIntent'

const API_BASE_URL = (import.meta.env.VITE_API_URL ?? '/api').replace(/\/$/, '')
const AUDIO_API_BASE_URL = (import.meta.env.VITE_AUDIO_API_URL ?? `${API_BASE_URL}/audio`).replace(
  /\/$/,
  ''
)

const audioApiUrl = (path: string) => `${AUDIO_API_BASE_URL}${path}`

// Derive a readable chapter title from the uploaded filename
function chapterTitle(filename: string, index: number): string {
  const base = filename.replace(/\.[^.]+$/, '')
  const parts = base.split('_')
  // Skip the first two segments when they look like a "bookid_lang" prefix
  const words = (parts.length > 2 ? parts.slice(2) : parts).join(' ').replace(/-/g, ' ').trim()
  return words || `Chapter ${index + 1}`
}

export function MediaPlayerProvider({ children }: { children: React.ReactNode }) {
  const [track, setTrack] = useState<TrackInfo | null>(null)
  const [files, setFiles] = useState<AudioFile[]>([])
  const [currentFileIdx, setCurrentFileIdx] = useState(0)
  const [audioSrc, setAudioSrc] = useState<{ src: string; type: string } | null>(null)
  const [isLoading, setIsLoading] = useState(false)
  const [playing, setPlaying] = useState(false)

  // Ref so goToFile / advance never have stale closure on the files list
  const filesRef = useRef<AudioFile[]>([])
  // Holds the vidstack remote.play() registered by PlayStateSync
  const resumeRef = useRef<(() => void) | null>(null)

  const registerResume = useCallback((fn: () => void) => {
    resumeRef.current = fn
  }, [])

  const resumePlayback = useCallback(() => {
    resumeRef.current?.()
  }, [])

  const loadBook = useCallback(
    async (
      bookId: number,
      meta: { title: string; author: string; coverUrl?: string | null },
      startFileIdx = 0
    ) => {
      setPlayIntent()
      setIsLoading(true)
      try {
        const res = await fetch(audioApiUrl(`/public/${bookId}`), { credentials: 'include' })
        if (!res.ok) throw new Error(`audio list ${res.status}`)

        const raw: Array<{
          id: number
          original_filename: string
          mime_type: string
          duration_seconds: number | null
        }> = await res.json()

        if (!raw.length) throw new Error('No audio files available for this book')

        const audioFiles: AudioFile[] = raw.map((f, i) => ({
          id: f.id,
          title: chapterTitle(f.original_filename, i),
          mimeType: f.mime_type,
          durationSeconds: f.duration_seconds,
        }))

        // Build cumulative chapters (startSeconds only accurate when durations are known)
        let cumStart = 0
        const chapters: Chapter[] = audioFiles.map((f) => {
          const ch: Chapter = {
            id: String(f.id),
            title: f.title,
            startSeconds: cumStart,
            durationSeconds: f.durationSeconds ?? 0,
          }
          cumStart += f.durationSeconds ?? 0
          return ch
        })

        const newTrack: TrackInfo = {
          bookId: String(bookId),
          title: meta.title,
          author: meta.author,
          coverUrl: meta.coverUrl ?? null,
          totalDurationSeconds: cumStart,
          chapters,
          narrators: [],
          availableLanguages: [],
        }

        const idx = Math.min(startFileIdx, audioFiles.length - 1)
        filesRef.current = audioFiles
        setFiles(audioFiles)
        setCurrentFileIdx(idx)
        setTrack(newTrack)
        setAudioSrc({
          src: audioApiUrl(`/stream/${audioFiles[idx].id}`),
          type: audioFiles[idx].mimeType,
        })
      } finally {
        setIsLoading(false)
      }
    },
    []
  )

  const goToFile = useCallback((idx: number) => {
    const f = filesRef.current
    if (idx < 0 || idx >= f.length) return
    setPlayIntent()
    setCurrentFileIdx(idx)
    setAudioSrc({ src: audioApiUrl(`/stream/${f[idx].id}`), type: f[idx].mimeType })
  }, [])

  const advance = useCallback(() => {
    setCurrentFileIdx((prev) => {
      const f = filesRef.current
      if (prev >= f.length - 1) return prev
      const next = prev + 1
      setPlayIntent()
      setAudioSrc({ src: audioApiUrl(`/stream/${f[next].id}`), type: f[next].mimeType })
      return next
    })
  }, [])

  const dismiss = useCallback(() => {
    filesRef.current = []
    resumeRef.current = null
    setFiles([])
    setCurrentFileIdx(0)
    setTrack(null)
    setAudioSrc(null)
    setPlaying(false)
  }, [])

  return (
    <AudioContext.Provider
      value={{
        track,
        files,
        currentFileIdx,
        audioSrc,
        isLoading,
        playing,
        resumePlayback,
        onPlayingChange: setPlaying,
        registerResume,
        loadBook,
        goToFile,
        advance,
        dismiss,
      }}
    >
      {children}
    </AudioContext.Provider>
  )
}
