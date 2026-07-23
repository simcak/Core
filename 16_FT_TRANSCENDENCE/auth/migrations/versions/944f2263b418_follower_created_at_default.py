"""follower_created_at_default

Revision ID: 944f2263b418
Revises: 5bd6f3ded297
Create Date: 2026-06-10 20:40:56.271112

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '944f2263b418'
down_revision: Union[str, Sequence[str], None] = '5bd6f3ded297'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.alter_column(
        'followers', 'created_at',
        schema='auth',
        server_default=sa.text('now()'),
        existing_type=sa.DateTime(),
        existing_nullable=False,
    )


def downgrade() -> None:
    op.alter_column(
        'followers', 'created_at',
        schema='auth',
        server_default=None,
        existing_type=sa.DateTime(),
        existing_nullable=False,
    )