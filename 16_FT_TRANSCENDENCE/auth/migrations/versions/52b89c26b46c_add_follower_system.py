"""add_follower_system

Revision ID: 52b89c26b46c
Revises: 7f9b8c3d1a2b
Create Date: 2026-05-18 15:55:13.179998

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '52b89c26b46c'
down_revision: Union[str, Sequence[str], None] = '7f9b8c3d1a2b'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    """Upgrade schema."""
    # Create followers table
    op.create_table(
        'followers',
        sa.Column('id', sa.BigInteger(), nullable=False),
        sa.Column('follower_id', sa.BigInteger(), nullable=False),
        sa.Column('followed_id', sa.BigInteger(), nullable=False),
        sa.Column('created_at', sa.DateTime(), nullable=False),
        sa.ForeignKeyConstraint(['follower_id'], ['users.id'], ondelete='CASCADE'),
        sa.ForeignKeyConstraint(['followed_id'], ['users.id'], ondelete='CASCADE'),
        sa.PrimaryKeyConstraint('id'),
        sa.UniqueConstraint('follower_id', 'followed_id', name='uq_follower')
    )


def downgrade() -> None:
    """Downgrade schema."""
    op.drop_table('followers')
