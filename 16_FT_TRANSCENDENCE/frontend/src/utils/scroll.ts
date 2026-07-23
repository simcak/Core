/**
 * Helper to handle smooth scrolling logic
 */
export const handleScroll = (
  ref: React.RefObject<HTMLDivElement | null>,
  dir: 'left' | 'right',
  distance: number = 400
) => {
  ref.current?.scrollBy({
    left: dir === 'right' ? distance : -distance,
    behavior: 'smooth',
  })
}
