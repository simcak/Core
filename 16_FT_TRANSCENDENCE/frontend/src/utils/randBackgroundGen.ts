// utils/randBackgroundGen.ts

function seededInt(seed: number, min: number, max: number, offset = 0): number {
  return (
    Math.floor((((seed * 9301 + offset * 49297 + 233) % 233280) / 233280) * (max - min + 1)) + min
  )
}

export function generateBookBackground(id: string | number): string {
  const seed = [...String(id)].reduce((acc, ch) => acc + ch.charCodeAt(0), 0)

  const layers = Array.from({ length: 4 }, (_, i) => {
    const hue = (seed * (i + 1) * 37) % 360
    const w = seededInt(seed, 30, 80, i * 10)
    const h = seededInt(seed, 30, 80, i * 20)
    const x = seededInt(seed, 10, 90, i * 30)
    const y = seededInt(seed, 10, 90, i * 40)
    return `radial-gradient(ellipse ${w}% ${h}% at ${x}% ${y}%, hsl(${hue}, 80%, 65%), transparent)`
  })

  const baseHue = seed % 360
  return [...layers, `hsl(${baseHue}, 50%, 30%)`].join(', ')
}
