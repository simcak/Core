"""add_default_libraries_trigger

Revision ID: ab31fe85edc0
Revises: c4d5e6f7a8b9
Create Date: 2026-06-19 00:50:24.816897

"""
from alembic import op

# revision identifiers, used by Alembic.
revision = 'ab31fe85edc0'
down_revision = 'c4d5e6f7a8b9'
branch_labels = None
depends_on = None

def upgrade() -> None:
    op.execute("""
        CREATE OR REPLACE FUNCTION auth.create_default_libraries()
        RETURNS TRIGGER AS $$
        BEGIN
            INSERT INTO auth.users_library (user_id, name)
            VALUES (NEW.id, 'Wishlist');
            RETURN NEW;
        END;
        $$ LANGUAGE plpgsql;
    """)

    op.execute("""
        CREATE OR REPLACE TRIGGER trg_create_default_libraries
        AFTER INSERT ON auth.users
        FOR EACH ROW EXECUTE FUNCTION auth.create_default_libraries();
    """)

def downgrade() -> None:
    op.execute("DROP TRIGGER IF EXISTS trg_create_default_libraries ON auth.users;")
    op.execute("DROP FUNCTION IF EXISTS auth.create_default_libraries();")