export interface Chapter {
  id: string
  title: string
  startSeconds: number
  durationSeconds: number
}

export interface NarratorInfo {
  id: string
  name: string
  isHuman: boolean
}

export interface TrackInfo {
  bookId: string
  title: string
  author: string
  coverUrl: string | null
  totalDurationSeconds: number
  chapters: Chapter[]
  narrators: NarratorInfo[]
  availableLanguages: string[]
}
