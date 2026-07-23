let _playIntended = false
export function setPlayIntent() {
  _playIntended = true
}
export function consumePlayIntent(): boolean {
  const v = _playIntended
  _playIntended = false
  return v
}
