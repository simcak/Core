import { toSlug } from './toSlug'

export type SearchField = 'title' | 'author' | 'category' | 'publisher' | 'description'
export type SearchResultType = 'book' | 'author' | 'publisher' | 'genre'

export interface SearchResult {
  id: number
  result_type: SearchResultType
  title: string
  author_name: string
  matched_field: SearchField
  matched_text: string
}

export function searchMatchLabel(field: SearchField) {
  switch (field) {
    case 'title':
      return 'Title'
    case 'author':
      return 'Author'
    case 'category':
      return 'Genre'
    case 'publisher':
      return 'Publisher'
    case 'description':
      return 'Description'
  }
}

export function searchResultPath(result: SearchResult) {
  if (result.result_type === 'author') return `/author/${result.id}`
  if (result.result_type === 'publisher') return `/publisher/${result.id}`
  if (result.result_type === 'genre') return `/genre/${toSlug(result.title)}`
  return `/book/${toSlug(result.title)}`
}

export function searchResultTypeLabel(result: SearchResult) {
  if (result.result_type === 'book') return result.author_name
  return `View ${result.author_name.toLowerCase()}`
}
