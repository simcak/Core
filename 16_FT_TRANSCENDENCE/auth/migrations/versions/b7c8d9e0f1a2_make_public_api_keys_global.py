"""make public api keys global

Revision ID: b7c8d9e0f1a2
Revises: a1b2c3d4e5f6
Create Date: 2026-06-18 00:00:00

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = "b7c8d9e0f1a2"
down_revision: Union[str, Sequence[str], None] = "a1b2c3d4e5f6"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.drop_index("ix_public_api_keys_user_id", table_name="public_api_keys")
    op.drop_constraint("public_api_keys_user_id_fkey", "public_api_keys", type_="foreignkey")
    op.drop_column("public_api_keys", "user_id")


def downgrade() -> None:
    op.add_column("public_api_keys", sa.Column("user_id", sa.BigInteger(), nullable=True))
    op.create_foreign_key(
        "public_api_keys_user_id_fkey",
        "public_api_keys",
        "users",
        ["user_id"],
        ["id"],
        ondelete="CASCADE",
    )
    op.create_index("ix_public_api_keys_user_id", "public_api_keys", ["user_id"])
