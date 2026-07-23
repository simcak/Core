import { useCallback } from 'react'

export const useApiFetch = () => {
  return useCallback((url: string, options: RequestInit = {}): Promise<Response> => {
    return fetch(url, {
      ...options,
      credentials: 'include',
      headers: {
        ...options.headers,
      },
    })
  }, [])
}
