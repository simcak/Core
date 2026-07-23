"""drop legacy password column

Revision ID: d7f4a2b6c1a3
Revises: c2f1e3a0d9a1
Create Date: 2026-05-02 09:22:00

"""
from typing import Sequence, Union

from alembic import op


# revision identifiers, used by Alembic.
revision: str = "d7f4a2b6c1a3"
down_revision: Union[str, Sequence[str], None] = "c2f1e3a0d9a1"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.execute("ALTER TABLE users DROP COLUMN IF EXISTS password")


def downgrade() -> None:
    op.execute("ALTER TABLE users ADD COLUMN IF NOT EXISTS password TEXT")
