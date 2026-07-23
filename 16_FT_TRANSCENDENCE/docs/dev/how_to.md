# How To

## How to add a new endpoint

1. **Choose the right service** — figure out which service owns the data you need. If it's book-related it goes in catalog, user-related in auth, etc.

2. **Update the model** — open `models.py` in that service and add a new class for the table (if it doesn't exist yet), or add missing columns to an existing one.

3. **Create a migration** — once the model reflects what you want, generate a migration:
   ```bash
   alembic -c migrations/alembic.ini revision -m "describe what changed"
   ```
   Open the generated file in `migrations/versions/` and fill in the `upgrade()` function with the actual `op.create_table()` or `op.add_column()` calls. Don't forget `downgrade()`.

4. **Apply and verify** — rebuild the image and restart the stack, then check the migration ran:
   ```bash
   docker compose build <service>
   docker compose up -d
   docker exec -it postgres psql -U transcendence -d transcendence -c "SET search_path TO <schema>; \dt"
   ```

5. **Add the Pydantic schema** — open `schemas.py` and add a response class for the new endpoint. Only include fields that should be visible in the API response — never expose passwords or internal flags.

6. **Add the route** — open `router.py` and add the new endpoint with a `response_model`:
   ```python
   @app.get("/your-resource", response_model=list[YourResponse])
   def get_your_resource(db: Session = Depends(get_db)):
       ...
   ```

7. **Test it** — rebuild and run a curl command to verify the response looks right:
   ```bash
   curl http://localhost:8080/api/<service>/your-resource
   ```

8. **Wire up the frontend** — add the API call in the relevant page or component, render the data, and check the browser console for errors.

---

## How to run the frontend separately (local dev mode)

By default `docker compose up -d` runs everything including the frontend container. That's fine for testing the full stack, but when you're actively working on the frontend it's much faster to run Vite directly — you get hot reload, instant updates, and better error messages.

**One-time setup (do this once after cloning):**

1. Install frontend dependencies:
   ```bash
   cd frontend
   npm install
   ```

2. Make sure your `.env` file in the repo root has `CORS_ORIGINS` set — without this the browser will block all API requests with a CORS error:
   ```
   CORS_ORIGINS=http://localhost:5173
   ```
   Check `.env.example` for the full list of required variables.

3. Create the local Vite env file (already gitignored, won't affect others):
   ```bash
   echo "VITE_API_URL=http://localhost:8080/api" > frontend/.env.development.local
   ```

**Running it:**

Start the full stack normally:
```bash
docker compose up -d
```

Then in a separate terminal start Vite:
```bash
cd frontend && npm run dev
```

Or use the convenience script from `package.json` which does both in one go:
```bash
cd frontend
npm run dev:local
```

Open `http://localhost:5173` in the browser. API requests go to `localhost:8080` (nginx) which routes them to the backend services as normal.

**Note:** `docker compose up -d` without running Vite separately still works — the frontend runs inside Docker as usual on port 8080.

---

## Frontend — setup after cloning

After cloning or pulling changes that touch `frontend/`, always run:

```bash
make install
```

This installs Node dependencies and registers the Husky git hooks. Without this step, the pre-commit lint checks won't run on your machine.

---

## Frontend — linting and formatting

The project uses ESLint + Prettier enforced via Husky pre-commit hooks. Every commit automatically lints and formats staged `.ts`/`.tsx` files.

**Run lint manually:**
```bash
cd frontend
npm run lint
```

**Auto-fix all lint and formatting issues across the whole codebase:**
```bash
cd frontend
npx eslint . --fix
npx prettier --write "src/**/*.{ts,tsx}"
```

**IDE setup (PyCharm / WebStorm):**
- `Settings → Languages & Frameworks → JavaScript → Code Quality Tools → ESLint` → select **Automatic ESLint configuration**, enable **Run eslint --fix on save**
- `Settings → Languages & Frameworks → JavaScript → Prettier` → set package to `frontend/node_modules/prettier`, enable **On save**

**IDE setup (VS Code):**

Install two extensions:
- [ESLint](https://marketplace.visualstudio.com/items?itemName=dbaeumer.vscode-eslint)
- [Prettier - Code formatter](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode)

Then add this to your `.vscode/settings.json` (create the file if it doesn't exist):
```json
{
  "editor.formatOnSave": true,
  "editor.defaultFormatter": "esbenp.prettier-vscode",
  "editor.codeActionsOnSave": {
    "source.fixAll.eslint": "explicit"
  }
}
```

This formats with Prettier and runs ESLint fix on every save.

After this your editor fixes issues as you type and on every save — the pre-commit hook is a safety net for anything that slips through.

---

## Frontend — auth pattern

Auth state lives in `AuthProvider` (wraps the entire app in `App.tsx`). Use the `useAuth` hook to access it anywhere:

```ts
const { user, token, login, logout, isAuthorized } = useAuth()
```

- `token` — JWT string or null. Use this to check if a user is logged in.
- `login(username, role, token)` — call after a successful login API response. Persists to localStorage automatically.
- `logout()` — clears user and token from state and localStorage.
- `isAuthorized(role)` — returns true if the logged-in user has the given role.

**Making authenticated API requests:**

Use `useApiFetch` instead of raw `fetch` — it automatically injects the `Authorization: Bearer <token>` header:

```ts
const apiFetch = useApiFetch()
// use apiFetch(url, options) exactly like fetch()
```

**Protected routes:**

Routes that require login are wrapped in `<PrivateRoute>` in `App.tsx`. If there is no token, the user is redirected to `/login`. Public routes (home, book pages, genre pages) are outside `PrivateRoute` and accessible without login.

To add a new protected route:
```tsx
<Route element={<PrivateRoute />}>
    <Route path="/your-route" element={<YourPage />} />
</Route>
```
