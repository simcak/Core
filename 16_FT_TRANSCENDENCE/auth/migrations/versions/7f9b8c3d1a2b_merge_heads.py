"""merge d0588da5f87e and 6a2b3c4d5e6f

Revision ID: 7f9b8c3d1a2b
Revises: d0588da5f87e, 6a2b3c4d5e6f
Create Date: 2026-05-12 00:30:00

"""
from typing import Sequence, Union

from alembic import op


# revision identifiers, used by Alembic.
revision: str = "7f9b8c3d1a2b"
down_revision: Union[str, Sequence[str], None] = ("d0588da5f87e", "6a2b3c4d5e6f")
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # This is a merge migration to unify multiple heads.
    pass


def downgrade() -> None:
    pass
