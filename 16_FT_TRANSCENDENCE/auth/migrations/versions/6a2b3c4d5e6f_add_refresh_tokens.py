"""add refresh tokens table

Revision ID: 6a2b3c4d5e6f
Revises: 4d21b7a9c6ef
Create Date: 2026-05-12 00:00:00

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = "6a2b3c4d5e6f"
down_revision: Union[str, Sequence[str], None] = "d0588da5f87e"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.create_table(
        'refresh_tokens',
        sa.Column('id', sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column('token_hash', sa.String(length=255), nullable=False, unique=True),
        sa.Column('user_id', sa.BigInteger(), sa.ForeignKey('users.id'), nullable=False),
        sa.Column('created_at', sa.DateTime(), nullable=False, server_default=sa.text('CURRENT_TIMESTAMP')),
        sa.Column('expires_at', sa.DateTime(), nullable=False),
        sa.Column('revoked', sa.Boolean(), nullable=False, server_default=sa.text('false')),
    )


def downgrade() -> None:
    op.drop_table('refresh_tokens')
