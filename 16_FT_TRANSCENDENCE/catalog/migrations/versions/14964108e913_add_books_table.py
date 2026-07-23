"""add books table

Revision ID: 14964108e913
Revises: 
Create Date: 2026-04-15 09:46:33.292702

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '14964108e913'
down_revision: Union[str, Sequence[str], None] = None
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:

    op.create_table(
        "author",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("author_name", sa.Text(), nullable=False),
    )
    op.create_table(
        "publisher",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("publisher_name", sa.Text(), nullable=False),
    )

    op.create_table(
        "book",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("author_id", sa.BigInteger(), sa.ForeignKey("author.id"), nullable=False),
        sa.Column("publisher_id", sa.BigInteger(), sa.ForeignKey("publisher.id"), nullable=True),
        sa.Column("price", sa.Numeric(10, 2), nullable=False),
        sa.Column("currency", sa.String(3), nullable=False, server_default="EUR"),
        sa.Column("language_code", sa.String(10), nullable=True),
        sa.Column("isbn", sa.String(20), nullable=True, unique=True),
        sa.Column("product_status", sa.String(20), nullable=False, server_default="draft"),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.text("CURRENT_TIMESTAMP")),
        sa.Column("updated_at", sa.DateTime(), nullable=False, server_default=sa.text("CURRENT_TIMESTAMP")),
    )

    op.create_table(
        "book_translations",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("book_id", sa.BigInteger(), sa.ForeignKey("book.id", ondelete="CASCADE"), nullable=False),
        sa.Column("lang", sa.String(10), nullable=False),
        sa.Column("title", sa.String(255), nullable=False),
        sa.Column("description", sa.Text(), nullable=True),
        sa.Column("cover_image_filename", sa.Text(), nullable=True),
        sa.Column("sample_url", sa.Text(), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.text("CURRENT_TIMESTAMP")),
        sa.Column("updated_at", sa.DateTime(), nullable=False, server_default=sa.text("CURRENT_TIMESTAMP")),
        sa.UniqueConstraint("book_id", "lang", name="uq_book_translations_book_lang"),
    )
    op.create_table(
        "book_category",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("parent_id", sa.BigInteger(), sa.ForeignKey("book_category.id"), nullable=True),
        sa.Column("category_name", sa.Text(), nullable=False),
    )
    op.create_table(
        "book_book_category",
        sa.Column("book_id", sa.BigInteger(), sa.ForeignKey("book.id", ondelete="CASCADE"), nullable=False),
        sa.Column(
            "category_id",
            sa.BigInteger(),
            sa.ForeignKey("book_category.id", ondelete="CASCADE"),
            nullable=False,
        ),
        sa.PrimaryKeyConstraint("book_id", "category_id", name="pk_book_book_category"),
    )

def downgrade() -> None:
    op.drop_table("book_book_category")
    op.drop_table("book_category")
    op.drop_table("book_translations")
    op.drop_table("book")
    op.drop_table("publisher")
    op.drop_table("author")
