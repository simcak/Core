import os
import re
from pathlib import Path


BASE_DIR = Path(__file__).resolve().parent
TEXT_FILE = BASE_DIR / "the_Republic.en.txt"
OUTPUT_DIR = BASE_DIR / "output_chunks"

VOICE_ID = "EkK5I93UQWFDigLMpZcX"
MODEL_ID = "eleven_v3"
OUTPUT_FORMAT = "mp3_44100_128"

# ElevenLabs documentation and product pages do not currently agree on the
# exact v3 input limit, so keep chunks conservative.
MAX_CHARS = 2500

# If you want to paste a long passage directly into the script, put it here.
INLINE_TEXT = ""


def load_text() -> str:
    if INLINE_TEXT.strip():
        return INLINE_TEXT.strip()

    return TEXT_FILE.read_text(encoding="utf-8").strip()


def normalize_paragraphs(text: str) -> list[str]:
    paragraphs = []

    for block in re.split(r"\n\s*\n", text):
        cleaned = re.sub(r"\s+", " ", block).strip()
        if cleaned:
            paragraphs.append(cleaned)

    return paragraphs


def split_oversized_text(text: str, max_chars: int) -> list[str]:
    if len(text) <= max_chars:
        return [text]

    pieces = []
    current = ""

    def push(piece: str) -> None:
        if piece:
            pieces.append(piece.strip())

    for sentence in re.split(r"(?<=[.!?])\s+", text):
        sentence = sentence.strip()
        if not sentence:
            continue

        candidate = sentence if not current else f"{current} {sentence}"
        if len(candidate) <= max_chars:
            current = candidate
            continue

        if current:
            push(current)
            current = ""

        if len(sentence) <= max_chars:
            current = sentence
            continue

        for clause in re.split(r"(?<=[:;,])\s+", sentence):
            clause = clause.strip()
            if not clause:
                continue

            candidate = clause if not current else f"{current} {clause}"
            if len(candidate) <= max_chars:
                current = candidate
                continue

            if current:
                push(current)
                current = ""

            if len(clause) <= max_chars:
                current = clause
                continue

            words = clause.split()
            for word in words:
                candidate = word if not current else f"{current} {word}"
                if len(candidate) <= max_chars:
                    current = candidate
                else:
                    push(current)
                    current = word

    push(current)
    return pieces


def build_chunks(text: str, max_chars: int = MAX_CHARS) -> list[str]:
    chunks = []
    current = ""

    for paragraph in normalize_paragraphs(text):
        for piece in split_oversized_text(paragraph, max_chars):
            candidate = piece if not current else f"{current}\n\n{piece}"
            if len(candidate) <= max_chars:
                current = candidate
            else:
                chunks.append(current)
                current = piece

    if current:
        chunks.append(current)

    return chunks


def save_audio_chunks(chunks: list[str]) -> None:
    from elevenlabs.client import ElevenLabs

    api_key = os.environ.get("ELEVENLABS_API_KEY")
    if not api_key:
        raise RuntimeError("Set ELEVENLABS_API_KEY before running this script.")

    client = ElevenLabs(api_key=api_key)
    OUTPUT_DIR.mkdir(exist_ok=True)

    manifest_lines = []

    for index, chunk in enumerate(chunks, start=1):
        filename = f"the_republic_{index:03d}.mp3"
        output_path = OUTPUT_DIR / filename

        audio = client.text_to_speech.convert(
            text=chunk,
            voice_id=VOICE_ID,
            model_id=MODEL_ID,
            output_format=OUTPUT_FORMAT,
        )

        with output_path.open("wb") as file_obj:
            for audio_chunk in audio:
                file_obj.write(audio_chunk)

        manifest_lines.append(f"file '{filename}'")
        print(f"Wrote {output_path.name} ({len(chunk)} chars)")

    (OUTPUT_DIR / "ffmpeg_concat.txt").write_text(
        "\n".join(manifest_lines) + "\n",
        encoding="utf-8",
    )


def main() -> None:
    text = load_text()
    chunks = build_chunks(text)

    print(f"Prepared {len(chunks)} chunk(s) from {len(text)} characters.")
    save_audio_chunks(chunks)


if __name__ == "__main__":
    main()
