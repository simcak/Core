// Shared slug function — same logic used in GenrePage and now BookPage.
// "The Martian" → "the-martian", "It" → "it"
export const toSlug = (text: string) =>
  text
    .toLowerCase()
    .replace(/\s+/g, '-')
    .replace(/[^a-z0-9-]/g, '')
