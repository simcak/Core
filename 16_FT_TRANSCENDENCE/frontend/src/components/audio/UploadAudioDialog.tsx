import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog.tsx'
import { useState } from 'react'
import { useTranslation } from 'react-i18next'
import { useApiFetch } from '@/hooks/useApiFetch.ts'
import { Input } from '@/components/ui/input.tsx'
import { Button } from '@/components/ui/button.tsx'
// import { uploadToPresignedUrl } from '@/utils/audioUpload.ts'

const ALLOWED_TYPES = ['audio/mpeg', 'audio/wav', 'audio/ogg', 'audio/mp4', 'audio/aac']

interface UploadAudioDialogProps {
  bookId: string
  open: boolean
  onOpenChange: (open: boolean) => void
  onSuccess: () => void
}

export default function UploadAudioDialog({
  bookId,
  open,
  onOpenChange,
  onSuccess,
}: UploadAudioDialogProps) {
  const { t } = useTranslation()
  const [file, setFile] = useState<File | null>(null)
  const [isLoading, setIsLoading] = useState(false)
  const [error, setError] = useState<string | null>(null)
  // const [progress, setProgress] = useState<number | null>(null)
  const apiFetch = useApiFetch()
  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const selected = e.target.files?.[0] ?? null
    setError(null)
    setFile(null)
    if (!selected) return
    if (!ALLOWED_TYPES.includes(selected.type)) {
      setError(t('uploadAudio.typeNotAllowed'))
      return
    }
    if (selected.size > 500 * 1024 * 1024) {
      setError(t('uploadAudio.sizeExceeded'))
      return
    }
    setFile(selected)
  }

  // const handleSubmit_presigned = async () => {
  //   if (!file) return
  //   setIsLoading(true)
  //   setError(null)
  //   setProgress(0)
  //   try {
  //     const presignRes = await apiFetch('/api/audio/presign', {
  //       method: 'POST',
  //       headers: { 'Content-Type': 'application/json' },
  //       body: JSON.stringify({
  //         book_id: parseInt(bookId),
  //         filename: file.name,
  //         content_type: file.type,
  //         size: file.size,
  //       }),
  //     })
  //     if (!presignRes.ok) throw new Error('Failed to get upload URL')
  //     const { upload_url, object_key } = await presignRes.json()
  //
  //     await uploadToPresignedUrl(upload_url, file, setProgress)
  //
  //     const registerRes = await apiFetch('/api/audio/files/register', {
  //       method: 'POST',
  //       headers: { 'Content-Type': 'application/json' },
  //       body: JSON.stringify({
  //         book_id: parseInt(bookId),
  //         object_key,
  //         original_filename: file.name,
  //         file_size: file.size,
  //         mime_type: file.type,
  //       }),
  //     })
  //     if (!registerRes.ok) throw new Error('Failed to register file')
  //
  //     setFile(null)
  //     setProgress(null)
  //     onSuccess()
  //     onOpenChange(false)
  //   } catch (e) {
  //     setError(e instanceof Error ? e.message : 'Upload failed')
  //     setProgress(null)
  //   } finally {
  //     setIsLoading(false)
  //   }
  // }

  const handleSubmit = async () => {
    if (!file) return
    setIsLoading(true)
    setError(null)
    try {
      const fd = new FormData()
      fd.append('file', file)
      fd.append('book_id', bookId)
      const res = await apiFetch('/api/audio/upload', { method: 'POST', body: fd })
      if (!res.ok) throw new Error(`Upload failed: ${res.status}`)
      setFile(null)
      onSuccess()
      onOpenChange(false)
    } catch (e) {
      setError(e instanceof Error ? e.message : 'Upload failed')
    } finally {
      setIsLoading(false)
    }
  }

  return (
    <Dialog open={open} onOpenChange={onOpenChange}>
      <DialogContent className="sm:max-w-lg">
        <DialogHeader>
          <DialogTitle>{t('uploadAudio.title')}</DialogTitle>
          <DialogDescription>{t('uploadAudio.description', { bookId })}</DialogDescription>
        </DialogHeader>
        <div className="flex flex-col gap-4 py-2">
          <div className="flex flex-col gap-2">
            <label htmlFor="audio-file" className="cursor-pointer">
              <div
                className="border-2 border-dashed border-border hover:border-primary rounded-lg p-8
  text-center transition-colors"
              >
                <div className="flex flex-col items-center gap-2">
                  <p className="text-2xl">↑</p>
                  <p className="text-sm font-medium">{t('uploadAudio.clickToBrowse')}</p>
                  <p className="text-xs text-muted-foreground">{t('uploadAudio.maxSize')}</p>
                </div>
              </div>
              <Input
                id="audio-file"
                type="file"
                accept=".mp3,.wav,.ogg,.mp4,.aac,audio/*"
                onChange={handleFileChange}
                className="hidden"
              />
            </label>
          </div>

          {file && (
            <div className="rounded-md bg-muted px-3 py-2 text-sm">
              <span className="font-medium">{file.name}</span>
              <span className="text-muted-foreground ml-2">
                ({(file.size / 1024 / 1024).toFixed(2)}
                MB)
              </span>
            </div>
          )}
          {/*{progress !== null && (*/}
          {/*  <div className="flex items-center gap-2 text-sm">*/}
          {/*    <div className="flex-1 bg-muted rounded-full h-1.5">*/}
          {/*      <div*/}
          {/*        className="bg-primary h-1.5 rounded-full transition-all"*/}
          {/*        style={{ width: `${progress}%` }}*/}
          {/*      />*/}
          {/*    </div>*/}
          {/*    <span className="text-muted-foreground w-10 text-right">{progress}%</span>*/}
          {/*  </div>*/}
          {/*)}*/}
          {error && <p className="text-sm text-destructive">{error}</p>}
        </div>
        <DialogFooter>
          <Button variant="outline" onClick={() => onOpenChange(false)} disabled={isLoading}>
            {t('uploadAudio.cancel')}
          </Button>
          <Button onClick={handleSubmit} disabled={!file || isLoading}>
            {isLoading ? t('uploadAudio.uploading') : t('uploadAudio.upload')}
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
