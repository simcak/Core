"""initial

Revision ID: 825bd5ccb44e
Revises: 
Create Date: 2026-04-10 23:52:05.205563

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '825bd5ccb44e'
down_revision: Union[str, Sequence[str], None] = None
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
	op.create_table(
		'role',
		sa.Column('id', sa.BigInteger(), primary_key=True, autoincrement=True),
		sa.Column('name', sa.String(50), nullable=False, unique=True),
	)

	op.create_table(
		'users',
		sa.Column('id', sa.BigInteger(), primary_key=True, autoincrement=True),
		sa.Column('username', sa.String(50), nullable=False, unique=True),
		sa.Column('email', sa.String(255), nullable=False, unique=True),
		sa.Column('password', sa.Text(), nullable=False),
		sa.Column('role_id', sa.BigInteger(), sa.ForeignKey('role.id'), nullable=False),
		sa.Column('status', sa.String(20), nullable=False, server_default='active'),
		sa.Column('first_name', sa.String(100)),
		sa.Column('last_name', sa.String(100)),
		sa.Column('avatar_filename', sa.Text()),
		sa.Column('phone', sa.String(30)),
		sa.Column('preferred_lang', sa.String(10), server_default='en'),
		sa.Column('last_login_at', sa.DateTime()),
		sa.Column('email_verified', sa.Boolean(), nullable=False, server_default=sa.text('false')),
		sa.Column('email_verified_at', sa.DateTime()),
		sa.Column('created_at', sa.DateTime(), nullable=False, server_default=sa.text('CURRENT_TIMESTAMP')),
		sa.Column('updated_at', sa.DateTime(), nullable=False, server_default=sa.text('CURRENT_TIMESTAMP')),
	)

def downgrade() -> None:
	op.drop_table('users')
	op.drop_table('role')

