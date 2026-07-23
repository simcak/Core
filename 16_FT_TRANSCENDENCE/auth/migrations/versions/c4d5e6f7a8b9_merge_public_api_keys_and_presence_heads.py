"""merge public api keys and presence heads

Revision ID: c4d5e6f7a8b9
Revises: 553c0b0bb854, b7c8d9e0f1a2
Create Date: 2026-06-18 00:00:00.000000

"""
from typing import Sequence, Union


# revision identifiers, used by Alembic.
revision: str = "c4d5e6f7a8b9"
down_revision: Union[str, Sequence[str], None] = ("553c0b0bb854", "b7c8d9e0f1a2")
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    """Merge migration branches."""
    pass


def downgrade() -> None:
    """Unmerge migration branches."""
    pass
