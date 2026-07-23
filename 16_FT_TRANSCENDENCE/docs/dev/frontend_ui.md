# Frontend UI — Dependencies & Architecture

Reference for the frontend toolchain: what we use, why, and how the pieces connect.

---

## Initial setup

Initially we started with Vite + raw React + Tailwind CSS.

Tailwind CSS wasn't actually used anywhere because we kept adding inline styles to the HTML.

We confirmed to introduce a new component library, shadcn.

Adding shadcn uncovered that we were using the older tailwind CSS version (v3). 

Upgrading to v4 showed that its conflicting with vite v8, which we had initially set up. So we had to downgrade to Vite 6.

So finally we have:
- typecript 6;
- react v19;
- vite v6 (stable, compatible with tailwind v4 and shadcn);
- tailwind v4 (latest);
- shadcn v4 (latest); 

---

## 1. Dependency Stack

### Build toolchain

| Package | Version | Role |
|---|---|---|
| `vite` | `^6.4` | Dev server + bundler |
| `@vitejs/plugin-react` | `^5.2` | JSX transform + Fast Refresh |
| `typescript` | `~6.0` | Type checking |
| `@types/react` / `@types/react-dom` | `^19` | React type definitions |

**Vite version history:**  
The project started with Vite 8. It was downgraded to Vite 6 because `@tailwindcss/vite@^4` declares a peer dependency of `vite ^5 \|\| ^6` and refuses to install against v8. Vite 8 also introduced `@rolldown/plugin-babel` as an internal dependency of `@vitejs/plugin-react@^6`, which was incompatible. Downgrading to Vite 6 + `@vitejs/plugin-react@^5` resolved both issues. **Do not upgrade Vite past 6 until `@tailwindcss/vite` explicitly supports it.**

---

### Styling

| Package | Version | Role |
|---|---|---|
| `tailwindcss` | `^4` | Utility CSS framework |
| `@tailwindcss/vite` | `^4.3` | Vite plugin — replaces PostCSS pipeline |
| `tw-animate-css` | `^1.4` | Pre-built CSS animations imported in `globals.css` |

**Tailwind v3 → v4 migration:**  
The project was initialised with Tailwind v3, which required `postcss.config.js`, `tailwind.config.js`, and `@tailwind base/components/utilities` directives in CSS. These were all replaced:

| v3 | v4 |
|---|---|
| `postcss.config.js` | Deleted — `@tailwindcss/vite` handles processing |
| `tailwind.config.js` | Deleted — custom theme goes in `@theme inline {}` in CSS |
| `@tailwind base/components/utilities` | `@import "tailwindcss"` at top of main CSS file |
| `extend.colors` in config | CSS variables defined in `:root` / `.dark`, mapped in `@theme inline` |

Custom theme and shadcn CSS variables live in `src/styles/globals.css`. The `:root` block defines light mode, `.dark` defines dark mode (oklch color values). The `@theme inline` block maps those CSS variables to Tailwind utility names (`--color-background: var(--background)` → enables `bg-background`).

Dark mode is enabled by adding `class="dark"` to `<html>` in `index.html`. The app is permanently dark — no toggle.

---

### Component library

| Package | Version | Role |
|---|---|---|
| `shadcn` | `^4.7` | CLI tool for adding components |
| `radix-ui` | `^1.4` | Headless UI primitives (Dialog, Label, Slot, etc.) |
| `class-variance-authority` | `^0.7` | Manages component variants (`cva()`) |
| `clsx` | `^2.1` | Merges conditional class strings |
| `tailwind-merge` | `^3.5` | Resolves conflicting Tailwind classes at runtime |
| `lucide-react` | `^1.14` | Icon set used by shadcn and throughout the UI |

**shadcn is a CLI, not a runtime dependency.** Running `npx shadcn@latest add <component>` copies component source into `src/components/ui/`. The components are owned by the project — edit them directly.

**Style preset:** `radix-nova` (selected at init). This affects the visual language of generated components.

**Path alias requirement:** shadcn reads `compilerOptions.paths` from the root `tsconfig.json` to resolve the `@/` alias. The root `tsconfig.json` must contain:
```json
{
  "compilerOptions": {
    "baseUrl": ".",
    "paths": { "@/*": ["./src/*"] }
  }
}
```
Without this, shadcn creates a literal `@/` directory at the project root instead of writing to `src/`.

---

### Routing & i18n

| Package | Version | Role |
|---|---|---|
| `react-router-dom` | `^7.14` | Client-side routing |
| `i18next` | `^26` | i18n core |
| `react-i18next` | `^17` | React bindings for i18next |

---

### Dev tooling

| Package | Version | Role |
|---|---|---|
| `eslint` | `^9.39` | Linting (flat config format — `eslint.config.js`) |
| `eslint-config-prettier` | `^10` | Disables ESLint rules that conflict with Prettier |
| `prettier` | `^3.8` | Code formatting |
| `husky` | `^9.1` | Git hooks (uses `core.hooksPath`, not `.git/hooks`) |
| `lint-staged` | `^16` | Runs ESLint + Prettier on staged files only |

Pre-commit hook runs `eslint --fix` + `prettier --write` on every staged `.ts/.tsx` file.

---

## 2. Dependency Diagram

How the layers depend on each other at runtime and build time.

```
┌─────────────────────────────────────────────────────────────┐
│                        Browser                              │
└──────────────────────────┬──────────────────────────────────┘
                           │ renders
┌──────────────────────────▼──────────────────────────────────┐
│                    React 19 + TSX                           │
│                                                             │
│  ┌─────────────────┐   ┌──────────────────────────────────┐ │
│  │    Routing      │   │         Application state        │ │
│  │                 │   │                                  │ │
│  │ react-router-dom│   │  AuthProvider (React Context)    │ │
│  │  <BrowserRouter>│   │  MediaPlayerProvider             │ │
│  │  <Route>        │   │  useAuth()                       │ │
│  │  <PrivateRoute> │   │  useApiFetch()  ──► fetch() API  │ │
│  └─────────────────┘   └──────────────────────────────────┘ │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐   │
│  │                    UI Components                     │   │
│  │                                                      │   │
│  │  src/pages/         src/components/                  │   │
│  │  └─ HomePage        └─ ui/           ← shadcn output │   │
│  │  └─ BookPage            └─ button.tsx                │   │
│  │  └─ ShelfPage           └─ dialog.tsx                │   │
│  │  └─ AdminUsersList      └─ input.tsx                 │   │
│  │  				         └─ table.tsx  ...            │   │
│  │                     └─ layout/       ← custom        │   │
│  │                     └─ home/                         │   │
│  │                     └─ book/                         │   │
│  └──────────────────────────────────────────────────────┘   │
└──────────────────────────┬──────────────────────────────────┘
                           │ styles from
┌──────────────────────────▼──────────────────────────────────┐
│                      Styling layer                          │
│                                                             │
│  src/styles/globals.css                                     │
│  ├── @import "tailwindcss"    ← Tailwind v4 entry point     │
│  ├── @import "tw-animate-css" ← animation utilities         │
│  ├── @custom-variant dark     ← .dark class activates vars  │
│  ├── @theme inline { ... }    ← maps CSS vars → TW names    │
│  │       --color-background: var(--background)              │
│  │       --color-primary: var(--primary)  ...               │
│  ├── :root { ... }            ← light mode CSS variables    │
│  └── .dark { ... }            ← dark mode CSS variables     │
│                                                             │
│  src/index.css                                              │
│  ├── @import './styles/globals.css'                         │
│  └── body, layout, login-page custom CSS                    │
│                                                             │
│  shadcn components use:                                     │
│    clsx() + tailwind-merge() → cn()  ← merges class strings │
│    cva()                             ← variant definitions  │
│    radix-ui primitives               ← accessible behaviour │
└──────────────────────────┬──────────────────────────────────┘
                           │ built by
┌──────────────────────────▼──────────────────────────────────┐
│                      Build toolchain                        │
│                                                             │
│  Vite 6                                                     │
│  ├── @vitejs/plugin-react   → JSX transform, Fast Refresh   │
│  ├── @tailwindcss/vite      → scans files, generates CSS    │
│  │     └── reads @import "tailwindcss" in globals.css       │
│  │     └── scans all .tsx for class names used              │
│  │     └── emits only the utility classes actually used     │
│  └── resolve.alias: @/ → src/                               │
│                                                             │
│  TypeScript ~6.0                                            │
│  └── tsconfig.app.json  ← strict, erasableSyntaxOnly        │
│  └── tsconfig.node.json ← for vite.config.ts itself         │
│  └── tsconfig.json      ← project references + @/ paths     │
└─────────────────────────────────────────────────────────────┘

Dev tooling (not in bundle):
  ESLint (flat config) ──► eslint-plugin-react-hooks
                       └─► eslint-config-prettier
  Prettier
  Husky (pre-commit) ──► lint-staged ──► eslint --fix + prettier --write
```

---

## Key rules

- **Do not upgrade Vite past 6** until it officially supported by tailwind
- **No `tailwind.config.js` or `postcss.config.js`** — v4 does not need them
- **`@import "tailwindcss"` must be the first line in `globals.css`** — the Vite plugin looks for it
- **`index.html` must have `class="dark"` on `<html>`** — shadcn CSS variables default to light mode
- **After `npx shadcn add`** — verify components landed in `src/components/ui/`, not a root `@/` folder
- **`cn()` from `@/lib/utils`** — always use this instead of raw `clsx` or `twMerge` in components
