# Frontend

← Back to [tools overview](../tools.md)

The entire frontend is a single-page app in `frontend/src`.

## React

**What:** the frontend UI framework. *(React 19 + TypeScript)*

**Why:** component-based architecture, a huge ecosystem, and the team's familiarity. Counts as our frontend framework for the Web module.

**Scope:** routing, state, and all UI components.

## Vite

**What:** the frontend build tool and dev server. *(v6)*

**Why:** near-instant hot-module reload in development and an optimized production bundle. Much faster than older bundlers.

**Scope:** builds the React app; `make frontend` runs the Vite dev server on `localhost:5173` for hot-reload development outside Docker.

## TypeScript

**What:** typed superset of JavaScript. *(v6)*

**Why:** catches type errors at build time and makes the component API self-documenting across five developers.

## Tailwind CSS

**What:** utility-first CSS framework. *(v4, via `@tailwindcss/vite`)*

**Why:** styling lives in the markup as utility classes — no separate CSS files to keep in sync, consistent design tokens out of the box.

## shadcn/ui & Radix UI

**What:** the component library. shadcn/ui provides copy-in, Tailwind-styled components built on top of **Radix UI** primitives.

**Why:** accessible, unstyled primitives (dialogs, dropdowns, etc.) that we style with Tailwind — we own the component code rather than depending on a black-box library.

## Supporting frontend libraries

| Library | Role |
|---|---|
| `react-router-dom` | Client-side routing |
| `@tanstack/react-table` | Data tables (book/audio lists) |
| `@vidstack/react` | Audio/media player |
| `i18next` + `react-i18next` | Internationalization |
| `react-day-picker` + `date-fns` | Date picking & formatting |
| `lucide-react` | Icon set |
| `sonner` | Toast notifications |
| `clsx` / `tailwind-merge` / `class-variance-authority` | Conditional class composition |
