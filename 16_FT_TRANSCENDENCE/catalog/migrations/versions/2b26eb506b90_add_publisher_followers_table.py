"""add publisher followers table

Revision ID: 2b26eb506b90
Revises: 14964108e913
Create Date: 2026-06-15 00:00:00.000000

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '2b26eb506b90'
down_revision: Union[str, Sequence[str], None] = '14964108e913'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.create_table(
        "publisher_followers",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("user_id", sa.BigInteger(), nullable=False),
        sa.Column(
            "publisher_id",
            sa.BigInteger(),
            sa.ForeignKey("publisher.id", ondelete="CASCADE"),
            nullable=False,
        ),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.text("CURRENT_TIMESTAMP")),
        sa.UniqueConstraint("user_id", "publisher_id", name="uq_publisher_follower"),
    )


def downgrade() -> None:
    op.drop_table("publisher_followers")
