export interface BookTranslation {
  lang: string
  title: string
  description: string | null
  cover_image_filename: string | null
  sample_url: string | null
}

export interface Author {
  id: number
  author_name: string
}

export interface Publisher {
  id: number
  publisher_name: string
}

export interface BookCategory {
  id: number
  category_name: string
}

export interface Book {
  id: number
  author: Author
  publisher: Publisher | null
  translations: BookTranslation[]
  categories: BookCategory[]
  price: number
  currency: string
  language_code: string | null
  isbn: string | null
  product_status: string
}

export interface ShortBook {
  id: number
  author: Author
  translations: BookTranslation[]
  price: number
  currency: string
  language_code: string | null
  product_status: string
}

export interface BookShelfEntry {
  id: string
  label: string
  checked: boolean
}

export interface Review {
  id: number
  user_id: number
  username: string
  rating: number
  text: string | null
  created_at: string
}

export interface BookReviewsData {
  average_rating: number | null
  count: number
  reviews: Review[]
}
