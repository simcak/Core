import { useState, useRef, useLayoutEffect } from 'react'
import { createPortal } from 'react-dom'
import { useMediaState, useMediaRemote } from '@vidstack/react'
import { useAudioContext } from './MPContextDef'
import { IconButton } from './IconButton'
import { generateBookBackground } from '../../utils/randBackgroundGen'
import {
  PlayIcon,
  PauseIcon,
  SkipBackIcon,
  SkipForwardIcon,
  Rewind10Icon,
  Forward10Icon,
  VolumeIcon,
  PencilIcon,
  MapIcon,
  ListIcon,
  GlobeIcon,
  NarratorIcon,
  AddIcon,
} from './icons'

// ─── Helpers ──────────────────────────────────────────────────────────────────

function formatTime(s: number): string {
  if (!isFinite(s) || s < 0) return '0:00'
  const h = Math.floor(s / 3600)
  const m = Math.floor((s % 3600) / 60)
  const sec = Math.floor(s % 60)
  if (h > 0) return `${h}:${String(m).padStart(2, '0')}:${String(sec).padStart(2, '0')}`
  return `${m}:${String(sec).padStart(2, '0')}`
}

const PLAYBACK_RATES = [0.5, 0.75, 1, 1.25, 1.5, 1.75, 2, 2.5, 3]

// ─── Progress bar ─────────────────────────────────────────────────────────────

function ProgressBar() {
  const { track, files, currentFileIdx, goToFile } = useAudioContext()
  const currentTime = useMediaState('currentTime')
  const duration = useMediaState('duration')
  const remote = useMediaRemote()
  const [hovering, setHovering] = useState(false)
  const barRef = useRef<HTMLDivElement>(null)

  const n = files.length
  const totalDuration = track?.totalDurationSeconds ?? 0
  const hasDurations = totalDuration > 0

  // Cumulative offset of the current file in the full book timeline
  const cumulativeOffset = files
    .slice(0, currentFileIdx)
    .reduce((s, f) => s + (f.durationSeconds ?? 0), 0)

  // Overall progress (0..1) across the whole book. When per-file durations are
  // known we use real time; otherwise each file occupies an equal slice and we
  // interpolate within the current file using its own duration.
  let progress: number
  if (hasDurations) {
    progress = Math.min((cumulativeOffset + currentTime) / totalDuration, 1)
  } else if (n > 0) {
    const within = isFinite(duration) && duration > 0 ? currentTime / duration : 0
    progress = Math.min((currentFileIdx + within) / n, 1)
  } else {
    progress = 0
  }

  // Fractional start position of each file — used for the separator dots that
  // stitch every audio file into one continuous timeline.
  const fileStarts: number[] = []
  if (n > 1) {
    let cum = 0
    for (let i = 0; i < n; i++) {
      fileStarts.push(hasDurations ? cum / totalDuration : i / n)
      cum += files[i].durationSeconds ?? 0
    }
  }

  function handleClick(e: React.MouseEvent) {
    if (!barRef.current) return
    const rect = barRef.current.getBoundingClientRect()
    const ratio = Math.max(0, Math.min((e.clientX - rect.left) / rect.width, 1))

    if (n <= 1) {
      // Single file: seek within current file
      remote.seek(ratio * (isFinite(duration) && duration > 0 ? duration : 0))
      return
    }

    if (hasDurations) {
      // Map click position to a file + offset using real durations
      const targetTime = ratio * totalDuration
      let cum = 0
      for (let i = 0; i < n; i++) {
        const fileDur = files[i].durationSeconds ?? 0
        if (targetTime <= cum + fileDur || i === n - 1) {
          if (i === currentFileIdx) remote.seek(targetTime - cum)
          else goToFile(i)
          break
        }
        cum += fileDur
      }
      return
    }

    // Unknown durations: each file is an equal slice
    const target = Math.min(Math.floor(ratio * n), n - 1)
    if (target === currentFileIdx) {
      const within = ratio * n - target
      remote.seek(within * (isFinite(duration) && duration > 0 ? duration : 0))
    } else {
      goToFile(target)
    }
  }

  return (
    <div
      ref={barRef}
      onClick={handleClick}
      onMouseEnter={() => setHovering(true)}
      onMouseLeave={() => setHovering(false)}
      style={{
        position: 'relative',
        height: hovering ? '6px' : '3px',
        background: 'rgba(255,255,255,0.15)',
        borderRadius: '99px',
        cursor: 'pointer',
        transition: 'height 0.15s ease',
        flexShrink: 0,
      }}
    >
      {/* Filled portion */}
      <div
        style={{
          position: 'absolute',
          inset: 0,
          right: `${(1 - progress) * 100}%`,
          background: '#f97316',
          borderRadius: '99px',
        }}
      />

      {/* File separator dots — one per file start (only for multi-file books) */}
      {fileStarts.map((pos, i) => {
        const isPast = pos <= progress
        return (
          <div
            key={files[i].id}
            title={files[i].title}
            onClick={(e) => {
              e.stopPropagation()
              goToFile(i)
            }}
            style={{
              position: 'absolute',
              top: '50%',
              left: `${pos * 100}%`,
              transform: 'translate(-50%, -50%)',
              width: hovering ? '10px' : '6px',
              height: hovering ? '10px' : '6px',
              borderRadius: '50%',
              background: isPast ? '#f97316' : 'rgba(255,255,255,0.5)',
              border: '2px solid rgba(30,30,30,0.9)',
              transition: 'all 0.15s ease',
              cursor: 'pointer',
              zIndex: 2,
            }}
          />
        )
      })}

      {/* Thumb */}
      {hovering && (
        <div
          style={{
            position: 'absolute',
            top: '50%',
            left: `${progress * 100}%`,
            transform: 'translate(-50%, -50%)',
            width: '14px',
            height: '14px',
            borderRadius: '50%',
            background: '#f97316',
            boxShadow: '0 0 6px rgba(249,115,22,0.6)',
            zIndex: 3,
            pointerEvents: 'none',
          }}
        />
      )}
    </div>
  )
}

// ─── Speed picker popover ──────────────────────────────────────────────────────

function SpeedPicker({
  anchorRef,
  onClose,
}: {
  anchorRef: React.RefObject<HTMLDivElement | null>
  onClose: () => void
}) {
  const playbackRate = useMediaState('playbackRate')
  const remote = useMediaRemote()

  // Render in a portal so the popover can overflow above the media player bar
  // (the bar itself uses overflow: hidden for its rounded corners).
  // Measure the anchor in a layout effect rather than during render, since refs
  // must not be accessed while rendering.
  const [rect, setRect] = useState<DOMRect | null>(null)
  useLayoutEffect(() => {
    setRect(anchorRef.current?.getBoundingClientRect() ?? null)
  }, [anchorRef])

  if (!rect) return null

  return createPortal(
    <div
      onMouseLeave={onClose}
      style={{
        position: 'fixed',
        bottom: `${window.innerHeight - rect.top + 8}px`,
        left: `${rect.left + rect.width / 2}px`,
        transform: 'translateX(-50%)',
        background: 'rgba(25,25,25,0.97)',
        border: '1px solid rgba(255,255,255,0.12)',
        borderRadius: '10px',
        padding: '8px 4px',
        display: 'flex',
        flexDirection: 'column',
        gap: '2px',
        boxShadow: '0 8px 32px rgba(0,0,0,0.5)',
        zIndex: 1000,
        minWidth: '72px',
      }}
    >
      {PLAYBACK_RATES.slice()
        .reverse()
        .map((rate) => (
          <button
            key={rate}
            onClick={() => {
              remote.changePlaybackRate(rate)
              onClose()
            }}
            style={{
              background: playbackRate === rate ? 'rgba(249,115,22,0.15)' : 'none',
              border: 'none',
              borderRadius: '6px',
              color: playbackRate === rate ? '#f97316' : 'rgba(255,255,255,0.7)',
              fontSize: '12px',
              fontWeight: playbackRate === rate ? 700 : 400,
              padding: '5px 12px',
              cursor: 'pointer',
              textAlign: 'center',
              transition: 'all 0.1s',
            }}
          >
            {rate}×
          </button>
        ))}
    </div>,
    document.body
  )
}

// ─── Mini (collapsed) bar ─────────────────────────────────────────────────────

export function MiniBar({ onExpand }: { onExpand: () => void }) {
  const { track } = useAudioContext()
  const paused = useMediaState('paused')
  const currentTime = useMediaState('currentTime')
  const remote = useMediaRemote()

  return (
    <div
      onClick={onExpand}
      style={{
        display: 'flex',
        alignItems: 'center',
        padding: '0 12px 0 10px',
        gap: '10px',
        width: '100%',
        height: '100%',
        cursor: 'pointer',
      }}
    >
      {/* Cover */}
      <div
        style={{
          width: '40px',
          height: '40px',
          borderRadius: '6px',
          background: track ? generateBookBackground(track.bookId) : 'rgba(255,255,255,0.08)',
          flexShrink: 0,
          overflow: 'hidden',
        }}
        onClick={(e) => e.stopPropagation()}
      >
        {track?.coverUrl && (
          <img
            src={track.coverUrl}
            alt={track.title}
            onError={(e) => {
              e.currentTarget.style.display = 'none'
            }}
            style={{ width: '100%', height: '100%', objectFit: 'cover' }}
          />
        )}
      </div>

      {/* Title + author */}
      <div style={{ flex: 1, minWidth: 0 }}>
        <p
          style={{
            fontSize: '13px',
            fontWeight: 600,
            color: 'rgba(255,255,255,0.9)',
            whiteSpace: 'nowrap',
            overflow: 'hidden',
            textOverflow: 'ellipsis',
            lineHeight: 1.3,
          }}
        >
          {track?.title ?? '—'}
        </p>
        <p
          style={{
            fontSize: '11px',
            color: 'rgba(255,255,255,0.4)',
            whiteSpace: 'nowrap',
            overflow: 'hidden',
            textOverflow: 'ellipsis',
            lineHeight: 1.3,
          }}
        >
          {track?.author ?? '—'}
        </p>
      </div>

      {/* Controls */}
      <div
        onClick={(e) => e.stopPropagation()}
        style={{ display: 'flex', alignItems: 'center', gap: '2px', flexShrink: 0 }}
      >
        <div style={{ display: 'flex', alignItems: 'center' }}>
          <IconButton title="Skip back 10s" onClick={() => remote.seek(currentTime - 10)}>
            <Rewind10Icon />
          </IconButton>
        </div>

        <IconButton
          title={paused ? 'Play' : 'Pause'}
          onClick={() => remote.togglePaused()}
          size="lg"
        >
          {paused ? <PlayIcon size={20} /> : <PauseIcon size={20} />}
        </IconButton>

        <div style={{ display: 'flex', alignItems: 'center' }}>
          <IconButton title="Skip forward 10s" onClick={() => remote.seek(currentTime + 10)}>
            <Forward10Icon />
          </IconButton>
        </div>

        <div
          style={{
            width: '1px',
            height: '20px',
            background: 'rgba(255,255,255,0.1)',
            margin: '0 6px',
          }}
        />

        <IconButton title="Notes" onClick={(e) => e.stopPropagation()}>
          <PencilIcon />
        </IconButton>
      </div>
    </div>
  )
}

// ─── Expanded panel ───────────────────────────────────────────────────────────

export function ExpandedPanel({ onCollapse }: { onCollapse: () => void }) {
  const { track, files, currentFileIdx, goToFile } = useAudioContext()
  const paused = useMediaState('paused')
  const currentTime = useMediaState('currentTime')
  const duration = useMediaState('duration')
  const playbackRate = useMediaState('playbackRate')
  const muted = useMediaState('muted')
  const remote = useMediaRemote()
  const [showSpeed, setShowSpeed] = useState(false)
  const speedAnchorRef = useRef<HTMLDivElement>(null)

  const cumulativeOffset = files
    .slice(0, currentFileIdx)
    .reduce((s, f) => s + (f.durationSeconds ?? 0), 0)
  const totalDuration = track?.totalDurationSeconds ?? 0
  const effectiveTime = totalDuration > 0 ? cumulativeOffset + currentTime : currentTime
  const total =
    totalDuration > 0 ? totalDuration : isFinite(duration) && duration > 0 ? duration : 0

  const prevChapter = () => goToFile(currentFileIdx - 1)
  const nextChapter = () => goToFile(currentFileIdx + 1)
  const hasPrev = currentFileIdx > 0
  const hasNext = currentFileIdx < files.length - 1

  return (
    <div
      onClick={onCollapse}
      style={{
        display: 'flex',
        alignItems: 'stretch',
        gap: '16px',
        padding: '14px 16px',
        width: '100%',
        height: '100%',
      }}
    >
      {/* Cover */}
      <div
        style={{
          width: '100px',
          height: '100px',
          borderRadius: '8px',
          background: track ? generateBookBackground(track.bookId) : 'rgba(255,255,255,0.08)',
          flexShrink: 0,
          overflow: 'hidden',
        }}
        onClick={(e) => e.stopPropagation()}
      >
        {track?.coverUrl && (
          <img
            src={track.coverUrl}
            alt={track.title}
            onError={(e) => {
              e.currentTarget.style.display = 'none'
            }}
            style={{ width: '100%', height: '100%', objectFit: 'cover' }}
          />
        )}
      </div>

      {/* Main content */}
      <div
        style={{
          flex: 1,
          minWidth: 0,
          display: 'flex',
          flexDirection: 'column',
          justifyContent: 'space-between',
        }}
      >
        {/* Row 1: title + author + action icons */}
        <div style={{ display: 'flex', alignItems: 'flex-start', gap: '8px' }}>
          <div style={{ flex: 1, minWidth: 0 }}>
            <p
              style={{
                fontSize: '15px',
                fontWeight: 700,
                color: 'rgba(255,255,255,0.95)',
                whiteSpace: 'nowrap',
                overflow: 'hidden',
                textOverflow: 'ellipsis',
                lineHeight: 1.3,
              }}
            >
              {track?.title ?? '—'}
            </p>
            <p
              style={{
                fontSize: '12px',
                color: 'rgba(255,255,255,0.45)',
                whiteSpace: 'nowrap',
                overflow: 'hidden',
                textOverflow: 'ellipsis',
                lineHeight: 1.3,
              }}
            >
              {track?.author ?? '—'}
            </p>
          </div>

          <div
            style={{ display: 'flex', alignItems: 'center', gap: '0px', flexShrink: 0 }}
            onClick={(e) => e.stopPropagation()}
          >
            <IconButton title="Language">
              <GlobeIcon size={16} />
            </IconButton>
            <IconButton title="Narrator">
              <NarratorIcon size={16} />
            </IconButton>
            <IconButton title="Add to shelf">
              <AddIcon size={16} />
            </IconButton>
          </div>

          <div
            style={{
              width: '1px',
              height: '20px',
              background: 'rgba(255,255,255,0.1)',
              alignSelf: 'center',
              margin: '0 4px',
            }}
          />

          <div
            style={{ display: 'flex', alignItems: 'center', gap: '0px', flexShrink: 0 }}
            onClick={(e) => e.stopPropagation()}
          >
            <IconButton title="Notes">
              <PencilIcon size={16} />
            </IconButton>
            <IconButton title="Map / Overview">
              <MapIcon size={16} />
            </IconButton>
            <IconButton title="Chapter list">
              <ListIcon size={16} />
            </IconButton>
          </div>
        </div>

        {/* Row 2: progress bar + timestamps */}
        <div
          style={{ display: 'flex', flexDirection: 'column', gap: '4px' }}
          onClick={(e) => e.stopPropagation()}
        >
          <ProgressBar />
          <div style={{ display: 'flex', justifyContent: 'space-between' }}>
            <span style={{ fontSize: '10px', color: 'rgba(255,255,255,0.35)' }}>
              {formatTime(effectiveTime)}
            </span>
            <span style={{ fontSize: '10px', color: 'rgba(255,255,255,0.35)' }}>
              {total > 0 ? `-${formatTime(total - effectiveTime)}` : '—'}
            </span>
          </div>
        </div>

        {/* Row 3: playback controls */}
        <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between' }}>
          {/* Speed */}
          <div
            ref={speedAnchorRef}
            style={{ position: 'relative' }}
            onClick={(e) => e.stopPropagation()}
          >
            <IconButton
              title="Playback speed"
              onClick={() => setShowSpeed((s) => !s)}
              active={showSpeed}
            >
              <span
                style={{
                  fontSize: '11px',
                  fontWeight: 700,
                  fontFamily: 'monospace',
                  minWidth: '28px',
                  textAlign: 'center',
                }}
              >
                {playbackRate}×
              </span>
            </IconButton>
            {showSpeed && (
              <SpeedPicker anchorRef={speedAnchorRef} onClose={() => setShowSpeed(false)} />
            )}
          </div>

          {/* Core transport */}
          <div
            style={{ display: 'flex', alignItems: 'center', gap: '2px' }}
            onClick={(e) => e.stopPropagation()}
          >
            <IconButton title="Previous chapter" onClick={prevChapter} disabled={!hasPrev}>
              <SkipBackIcon size={18} />
            </IconButton>
            <IconButton title="Rewind 10s" onClick={() => remote.seek(currentTime - 10)}>
              <Rewind10Icon size={20} />
            </IconButton>
            <IconButton
              title={paused ? 'Play' : 'Pause'}
              onClick={() => remote.togglePaused()}
              size="lg"
            >
              {paused ? <PlayIcon size={24} /> : <PauseIcon size={24} />}
            </IconButton>
            <IconButton title="Forward 10s" onClick={() => remote.seek(currentTime + 10)}>
              <Forward10Icon size={20} />
            </IconButton>
            <IconButton title="Next chapter" onClick={nextChapter} disabled={!hasNext}>
              <SkipForwardIcon size={18} />
            </IconButton>
          </div>

          {/* Volume */}
          <IconButton
            title={muted ? 'Unmute' : 'Mute'}
            onClick={(e) => {
              e.stopPropagation()
              remote.toggleMuted()
            }}
          >
            <VolumeIcon size={17} muted={muted} />
          </IconButton>
        </div>
      </div>
    </div>
  )
}
