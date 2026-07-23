import os
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, DeclarativeBase

DATABASE_URL = (
    f"postgresql+psycopg://{os.getenv('DB_USER', 'transcendence')}:"
    f"{os.getenv('DB_PASSWORD', 'transcendence')}@"
    f"{os.getenv('DB_HOST', 'postgres')}:"
    f"{os.getenv('DB_PORT', '5432')}/"
    f"{os.getenv('DB_NAME', 'transcendence')}"
)

engine = create_engine(DATABASE_URL,
                       connect_args={"options": "-c search_path=auth"})
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)


class Base(DeclarativeBase):
    pass


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
