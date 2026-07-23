import os
import sys
from logging.config import fileConfig
from pathlib import Path

from sqlalchemy import create_engine, text, pool

from alembic import context

BASE_DIR = Path(__file__).resolve().parent.parent
if str(BASE_DIR) not in sys.path:
    sys.path.insert(0, str(BASE_DIR))

from database import Base
import models  # noqa: F401  # register ORM models on Base.metadata


# this is the Alembic Config object, which provides
# access to the values within the .ini file in use.
config = context.config

# Interpret the config file for Python logging.
# This line sets up loggers basically.
if config.config_file_name is not None:
    fileConfig(config.config_file_name)

DB_USER = os.getenv("DB_USER", "transcendence")
DB_PASSWORD = os.getenv("DB_PASSWORD", "transcendence")
DB_HOST = os.getenv("DB_HOST", "postgres")
DB_PORT = os.getenv("DB_PORT", "5432")
DB_NAME = os.getenv("DB_NAME", "transcendence")
SCHEMA = os.getenv("DB_SCHEMA", "audio")

DATABASE_URL = (
    f"postgresql+psycopg://{DB_USER}:{DB_PASSWORD}"
    f"@{DB_HOST}:{DB_PORT}/{DB_NAME}"
)

target_metadata = Base.metadata

def run_migrations() -> None:
    engine = create_engine(DATABASE_URL, poolclass=pool.NullPool)
    with engine.begin() as connection:
        connection.execute(text(f"CREATE SCHEMA IF NOT EXISTS {SCHEMA}"))
        connection.execute(text(f"SET search_path TO {SCHEMA}"))
        context.configure(
            connection=connection,
            target_metadata=target_metadata,
            version_table_schema=SCHEMA,
            include_object=lambda object_, name, type_, reflected, compare_to: name != "alembic_version",
        )
        with context.begin_transaction():
            context.run_migrations()

run_migrations()
