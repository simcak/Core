export interface User {
  username: string
  avatar_filename?: string | null
  role: { role_name: string }
}

export interface UserForAdmin {
  id: number
  username: string
  email: string
  first_name: string | null
  last_name: string | null
  phone: string | null
  role_id: number
  role: Role
  created_at: string
  updated_at: string
  last_login_at: string | null
  name: string
  status: 'active' | 'inactive'
}

export interface LoginResponse {
  access_token: string
  token_type: string
  user: User
}

export interface Role {
  id: number
  role_name: string
}

export interface DeleteConfirmModalProps {
  isOpen: boolean
  selectedUser: UserForAdmin | null
  onConfirm: () => void
  onClose: () => void
}

export interface SortHeaderProps {
  column: string
  label: string
  sortBy: string
  sortDir: 'asc' | 'desc'
  onToggle: (column: string) => void
}

export interface EditUserModalProps {
  isOpen: boolean
  selectedUser: UserForAdmin | null
  formData: Partial<UserForAdmin>
  setFormData: (data: Partial<UserForAdmin>) => void
  onSave: () => void
  onClose: () => void
}

// Books for Admin

export interface BookForAdmin {
  id: number
  title: string // derived: en translation or first translation
  author_name: string // derived: author.author_name
  publisher_name: string | null // derived: publisher?.publisher_name
  translations: {
    lang: string
    title: string
    description: string | null
    cover_image_filename: string | null
    sample_url: string | null
  }[]
  price: number
  currency: string
  language_code: string | null
  isbn: string | null
  product_status: string
}

export interface EditBookModalProps {
  isOpen: boolean
  selectedBook: BookForAdmin | null
  formData: Partial<BookForAdmin>
  setFormData: (data: Partial<BookForAdmin>) => void
  onSave: () => void
  onClose: () => void
}

export interface DeleteBookConfirmModalProps {
  isOpen: boolean
  selectedBook: BookForAdmin | null
  onConfirm: () => void
  onClose: () => void
}
