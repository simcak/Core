"""add password column (noop)

Revision ID: b9b7c0c2a8a1
Revises: 4d21b7a9c6ef
Create Date: 2026-05-01 09:36:00

"""
from typing import Sequence, Union


# revision identifiers, used by Alembic.
revision: str = "b9b7c0c2a8a1"
down_revision: Union[str, Sequence[str], None] = "4d21b7a9c6ef"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # No-op migration to satisfy existing alembic version.
    pass


def downgrade() -> None:
    pass
