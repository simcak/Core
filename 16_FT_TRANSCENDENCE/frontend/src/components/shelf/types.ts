export interface ShelfFolder {
  id: string
  label: string
  color: string
  bookIds: number[] // mock for now — will come from shelf API
}

// Temporary mock data. Replace with GET /api/shelf/folders once backend is ready.
export const INITIAL_FOLDERS: ShelfFolder[] = [
  { id: 'top', label: 'Top', color: '#d4a017', bookIds: [1, 2, 3, 4, 5] },
  { id: 'wishlist', label: 'Wish list', color: '#4caf50', bookIds: [6, 7, 8] },
  { id: 'finals', label: 'Final Exams', color: '#e53935', bookIds: [9, 10, 11] },
  { id: 'guilty', label: 'Guilty pleasure', color: '#ab47bc', bookIds: [12, 1, 3] },
  { id: 'category', label: 'Category', color: '#1e88e5', bookIds: [2, 5, 7, 10, 12] },
  { id: 'unfinished', label: 'Unfinished', color: '#26a69a', bookIds: [4, 6, 9] },
]

export const PALETTE = [
  '#e53935',
  '#e67c13',
  '#d4a017',
  '#43a047',
  '#00897b',
  '#1e88e5',
  '#5e35b1',
  '#ab47bc',
  '#f06292',
  '#ffffff',
]
