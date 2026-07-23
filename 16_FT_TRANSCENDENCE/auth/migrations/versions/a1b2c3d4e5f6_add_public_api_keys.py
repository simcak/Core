"""add public api keys table

Revision ID: a1b2c3d4e5f6
Revises: 5482c1231b50
Create Date: 2026-06-18 00:00:00

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = "a1b2c3d4e5f6"
down_revision: Union[str, Sequence[str], None] = "5482c1231b50"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.create_table(
        "public_api_keys",
        sa.Column("id", sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column("user_id", sa.BigInteger(), nullable=False),
        sa.Column("token_hash", sa.String(length=255), nullable=False),
        sa.Column("name", sa.String(length=100), nullable=False),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.func.now()),
        sa.Column("expires_at", sa.DateTime(), nullable=True),
        sa.Column("last_used_at", sa.DateTime(), nullable=True),
        sa.Column("revoked", sa.Boolean(), nullable=False, server_default=sa.text("false")),
        sa.ForeignKeyConstraint(["user_id"], ["users.id"], ondelete="CASCADE"),
    )
    op.create_index("ix_public_api_keys_user_id", "public_api_keys", ["user_id"])
    op.create_index("ix_public_api_keys_token_hash", "public_api_keys", ["token_hash"], unique=True)


def downgrade() -> None:
    op.drop_index("ix_public_api_keys_token_hash", table_name="public_api_keys")
    op.drop_index("ix_public_api_keys_user_id", table_name="public_api_keys")
    op.drop_table("public_api_keys")
