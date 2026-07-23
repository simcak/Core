"""expand auth catalog schema

Revision ID: 4d21b7a9c6ef
Revises: 825bd5ccb44e
Create Date: 2026-04-13 15:10:00

"""

from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = "4d21b7a9c6ef"
down_revision: Union[str, Sequence[str], None] = "825bd5ccb44e"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # Align role table with new naming and loosen uniqueness requirement.
    op.alter_column("role", "name", new_column_name="role_name")
    op.alter_column("role", "role_name", existing_type=sa.String(length=50), type_=sa.Text())
    op.drop_constraint("role_name_key", "role", type_="unique")




def downgrade() -> None:
    op.add_column("role", sa.Column("name", sa.String(length=50), nullable=False))
    op.execute("UPDATE role SET name = role_name")
    op.create_unique_constraint("role_name_key", "role", ["name"])
    op.drop_column("role", "role_name")
