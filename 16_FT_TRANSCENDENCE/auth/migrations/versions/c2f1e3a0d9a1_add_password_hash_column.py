"""add password_hash column

Revision ID: c2f1e3a0d9a1
Revises: b9b7c0c2a8a1
Create Date: 2026-05-01 15:52:00

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = "c2f1e3a0d9a1"
down_revision: Union[str, Sequence[str], None] = "b9b7c0c2a8a1"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.execute("ALTER TABLE users ADD COLUMN IF NOT EXISTS password_hash TEXT")
    op.execute(
        """
        DO $$
        BEGIN
            IF EXISTS (
                SELECT 1
                FROM information_schema.columns
                WHERE table_name = 'users' AND column_name = 'password'
            ) THEN
                EXECUTE 'UPDATE users SET password_hash = password WHERE password_hash IS NULL';
            END IF;
        END $$;
        """
    )


def downgrade() -> None:
    op.drop_column("users", "password_hash")
