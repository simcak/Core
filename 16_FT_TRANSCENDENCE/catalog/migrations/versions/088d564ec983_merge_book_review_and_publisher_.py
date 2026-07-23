"""merge book review and publisher followers

Revision ID: 088d564ec983
Revises: 3313d6d8fc42, 2b26eb506b90
Create Date: 2026-06-15 12:41:46.620442

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '088d564ec983'
down_revision: Union[str, Sequence[str], None] = ('3313d6d8fc42', '2b26eb506b90')
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    """Upgrade schema."""
    pass


def downgrade() -> None:
    """Downgrade schema."""
    pass
