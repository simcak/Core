"""add users_library and users_library_book tables

Revision ID: 5482c1231b50
Revises: 944f2263b418
Create Date: 2026-06-16 23:04:49.995805

"""
from typing import Sequence, Union
from alembic import op
import sqlalchemy as sa

# revision identifiers, used by Alembic.
revision: str = '5482c1231b50'
down_revision: Union[str, None] = '944f2263b418'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None

def upgrade():
    # 1. users_library
    op.create_table(
        'users_library',
        sa.Column('id',      sa.BigInteger(), primary_key=True, autoincrement=True),
        sa.Column('user_id', sa.Integer(),    nullable=False),
        sa.Column('name',    sa.String(100),  nullable=False),
        sa.ForeignKeyConstraint(
            ['user_id'], ['auth.users.id'],
            name='users_library_user_id_fkey',
            ondelete='CASCADE'
        ),
        sa.UniqueConstraint('user_id', 'name', name='uq_users_library_user_name'),
        schema='auth'
    )
    op.create_index('ix_users_library_user_id', 'users_library', ['user_id'], schema='auth')

    # 2. users_library_book
    op.create_table(
        'users_library_book',
        sa.Column('library_id', sa.BigInteger(), nullable=False),
        sa.Column('book_id',    sa.BigInteger(), nullable=False),
        sa.PrimaryKeyConstraint('library_id', 'book_id', name='users_library_book_pkey'),
        sa.ForeignKeyConstraint(
            ['library_id'], ['auth.users_library.id'],
            name='users_library_book_library_fkey',
            ondelete='CASCADE'
        ),
        sa.ForeignKeyConstraint(
            ['book_id'], ['catalog.book.id'],
            name='users_library_book_book_fkey',
            ondelete='CASCADE'
        ),
        schema='auth'
    )
    op.create_index('ix_users_library_book_book_id', 'users_library_book', ['book_id'], schema='auth')


def downgrade():
    op.drop_index('ix_users_library_book_book_id', table_name='users_library_book', schema='auth')
    op.drop_table('users_library_book', schema='auth')

    op.drop_index('ix_users_library_user_id', table_name='users_library', schema='auth')
    op.drop_table('users_library', schema='auth')
