"""alter_password_hash_varchar_not_null

Revision ID: d0588da5f87e
Revises: d7f4a2b6c1a3
Create Date: 2026-05-04 12:43:15.516032

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = 'd0588da5f87e'
down_revision: Union[str, Sequence[str], None] = 'd7f4a2b6c1a3'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.alter_column(
        "users", "password_hash",
        existing_type=sa.Text(),
        type_=sa.String(length=255),
        nullable=False
    )


def downgrade() -> None:
    op.alter_column(
        "users", "password_hash",
        existing_type=sa.String(length=255),
        type_=sa.Text(),
        nullable=True
    )
