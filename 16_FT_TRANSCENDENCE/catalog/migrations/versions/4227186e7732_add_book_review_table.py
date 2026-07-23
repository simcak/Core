"""add book review table

Revision ID: 4227186e7732
Revises: 14964108e913
Create Date: 2026-06-14 00:57:20.320447

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa

# revision identifiers, used by Alembic.
revision: str = '4227186e7732'
down_revision: Union[str, Sequence[str], None] = '14964108e913'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    """Upgrade schema."""
    op.create_table(
        "book_review",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("book_id", sa.BigInteger(), sa.ForeignKey("book.id", ondelete="CASCADE"), nullable=False),
        sa.Column("user_id", sa.BigInteger(), nullable=False),
        sa.Column("username", sa.String(100), nullable=False),
        sa.Column("rating", sa.SmallInteger(), nullable=False),
        sa.Column("text", sa.Text(), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_defaults=sa.text("CURRENT_TIMESTAMP")),
        sa.UniqueConstraint("book_id", "user_id", name="uq_book_review_book_user"),
    )


def downgrade() -> None:
    """Downgrade schema."""
    op.drop_table("book_review")
