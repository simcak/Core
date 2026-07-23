# Alembic — database migrations

← Back to [tools overview](../tools.md) · summary in [backend.md](backend.md#alembic).

Read througt the [tutorial](https://alembic.sqlalchemy.org/en/latest/tutorial.html#create-a-migration-script) first.

NullPool setup - migration runs and shuts down it should not keep connection open. Read [sqlalchemy.pool.NullPool](https://docs.sqlalchemy.org/en/20/core/pooling.html#sqlalchemy.pool.NullPool) for more info

Postgres [search path](https://www.postgresql.org/docs/current/runtime-config-client.html#GUC-SEARCH-PATH)

## Additional materials
https://medium.com/@tejpal.abhyuday/alembic-database-migrations-the-complete-developers-guide-d3fc852a6a9e


## How to start with alembic

Normally all this files are just boilerplate and you'll not be creating them yourself but jsut simply modifying generated files.

When creating a new serivce run these commands once:

```bash
cd auth
source .venv/bin/activate
pip install alembic                  # if not already in requirements.txt
alembic init migrations              # generates the migrations/ folder
```

alembic.ini - contains all the configurations. An important part is script_location = alembic
env.py - contains the alembic environment. Primarily boilerplate the only custom thing is schema setup
script.py.mako - contains the migration script template. Purely boilerplate copy and paste


## Creating first migration

```bash
cd auth
source .venv/bin/activate
alembic -c migrations/alembic.ini revision -m "initial"
```

## Adding another migration

The command below will create a new migration file to populate.

```bash
alembic -c migrations/alembic.ini revision -m "add tokens table"
```
### Known issues

```bash
alembic -c migrations/alembic.ini revision -m "initial"
FAILED: Path doesn't exist: alembic.  Please use the 'init' command to create a new scripts folder.
```

The issue is script_location = alembic is resolved relative to where you run the command, not where alembic.ini lives. So from auth/ it looks for auth/alembic/ which doesn't exist.

Use %(here)s as prefix — a built-in Alembic variable that means "the directory containing this ini file":

`script_location = %(here)s/alembic`


## Running migrations

```bash
DB_HOST=localhost DB_PORT=5434 alembic -c migrations/alembic.ini upgrade head
```