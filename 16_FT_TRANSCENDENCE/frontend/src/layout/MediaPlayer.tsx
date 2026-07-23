import { useState, useEffect } from 'react'
import {
  MediaPlayer,
  MediaProvider,
  useMediaState,
  useMediaRemote,
  type AudioSrc,
} from '@vidstack/react'
import { useAudioContext } from '../components/media-player'
import { consumePlayIntent } from '../components/media-player/playIntent'
import { MiniBar, ExpandedPanel } from '../components/media-player/MPBar'

// Triggers play once when the media becomes ready, but only if an explicit user
// action (loadBook / goToFile / advance) set the intent flag first. This prevents
// auto-play when the MediaPlayer remounts for structural reasons — e.g. the app
// layout re-mounts after the user logs back in with a stale audioSrc in context.
function AutoPlayer() {
  const canPlay = useMediaState('canPlay')
  const remote = useMediaRemote()

  useEffect(() => {
    if (canPlay && consumePlayIntent()) {
      remote.play()
    }
  }, [canPlay, remote])

  return null
}

// Syncs vidstack's real play/pause state into the AudioContext and registers
// the remote.play() function so BookHero's Resume button can trigger playback
// without re-loading the track.
function PlayStateSync() {
  const playing = useMediaState('playing')
  const remote = useMediaRemote()
  const { onPlayingChange, registerResume } = useAudioContext()

  useEffect(() => {
    onPlayingChange(playing)
  }, [playing, onPlayingChange])

  useEffect(() => {
    registerResume(() => {
      remote.play()
    })
  }, [remote, registerResume])

  return null
}

const MINI_HEIGHT = 60
const EXPANDED_HEIGHT = 152

export default function MediaPlayerBar() {
  const { track, audioSrc, advance } = useAudioContext()
  const [isExpanded, setIsExpanded] = useState(false)

  if (!audioSrc) return null

  return (
    <div
      dir="ltr"
      style={{
        position: 'fixed',
        bottom: '12px',
        left: 'calc(var(--left-sidebar-width, 0px) + 12px)',
        right: 'calc(var(--right-sidebar-width, 0px) + 12px)',
        height: isExpanded ? `${EXPANDED_HEIGHT}px` : `${MINI_HEIGHT}px`,
        background: 'rgba(22, 22, 22, 0.82)',
        backdropFilter: 'blur(20px)',
        WebkitBackdropFilter: 'blur(20px)',
        border: '1px solid rgba(255,255,255,0.09)',
        borderRadius: '16px',
        boxShadow: '0 8px 40px rgba(0,0,0,0.5), 0 1px 0 rgba(255,255,255,0.06) inset',
        zIndex: 50,
        overflow: 'hidden',
        transition: 'height 0.25s cubic-bezier(0.4, 0, 0.2, 1), left 0.2s ease, right 0.2s ease',
        color: 'rgba(255,255,255,0.85)',
      }}
    >
      <MediaPlayer
        key={audioSrc.src}
        title={track?.title ?? ''}
        src={audioSrc as AudioSrc}
        onEnded={advance}
        style={{ width: '100%', height: '100%' }}
      >
        <MediaProvider style={{ display: 'none' }} />
        <AutoPlayer />
        <PlayStateSync />

        {isExpanded ? (
          <ExpandedPanel onCollapse={() => setIsExpanded(false)} />
        ) : (
          <MiniBar onExpand={() => setIsExpanded(true)} />
        )}
      </MediaPlayer>
    </div>
  )
}
