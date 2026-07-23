import { PALETTE } from './types'

interface ColorPickerProps {
  current: string
  onPick: (color: string) => void
}

export default function ColorPicker({ current, onPick }: ColorPickerProps) {
  return (
    <div className="flex flex-wrap gap-1.5 px-2 py-1">
      {PALETTE.map((c) => (
        <button
          key={c}
          onClick={() => onPick(c)}
          style={{
            background: c,
            width: 18,
            height: 18,
            borderRadius: 4,
            outline: current === c ? '2px solid white' : '2px solid transparent',
            outlineOffset: 1,
          }}
        />
      ))}
    </div>
  )
}
