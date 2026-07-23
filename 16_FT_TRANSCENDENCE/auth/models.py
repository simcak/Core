import datetime
from sqlalchemy import BigInteger, ForeignKey, String, DateTime, Boolean, UniqueConstraint, func
from sqlalchemy.orm import Mapped, mapped_column, relationship
from database import Base


class Role(Base):
    __tablename__ = "role"

    id: Mapped[int] = mapped_column(primary_key=True)
    role_name: Mapped[str] = mapped_column(unique=True, index=True)


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(unique=True, index=True)
    email: Mapped[str] = mapped_column(unique=True, index=True)
    password_hash: Mapped[str] = mapped_column(String(255), nullable=True)  # changed to true due to oauth
    role_id: Mapped[int] = mapped_column(BigInteger, ForeignKey("role.id"), nullable=False)
    role: Mapped[Role] = relationship()
    status: Mapped[str] = mapped_column(String(20), nullable=False, server_default='active')
    first_name: Mapped[str | None] = mapped_column(String(150), nullable=True)
    last_name: Mapped[str | None] = mapped_column(String(150), nullable=True)
    avatar_filename: Mapped[str | None] = mapped_column(String(255), nullable=True)
    phone: Mapped[str | None] = mapped_column(String(30), nullable=True)
    last_login_at: Mapped[datetime.datetime | None] = mapped_column(DateTime, nullable=True)
    last_seen_at: Mapped[datetime.datetime | None] = mapped_column(DateTime, nullable=True)
    email_verified: Mapped[bool] = mapped_column(nullable=False, server_default='false')
    email_verified_at: Mapped[datetime.datetime | None] = mapped_column(DateTime, nullable=True)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    updated_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    refresh_tokens: Mapped[list["RefreshToken"]] = relationship(back_populates="user")

    __table_args__ = (
        UniqueConstraint(
            "oauth_provider",
            "oauth_id",
            name="uq_oauth_provider_id"
        ),
    )

    oauth_provider: Mapped[str | None] = mapped_column(String(50), nullable=True)
    oauth_id: Mapped[str | None] = mapped_column(String(255), nullable=True)
    followers: Mapped[list["Follower"]] = relationship(
        "Follower",
        foreign_keys="[Follower.followed_id]",
        back_populates="followed",
        passive_deletes=True
    )
    following: Mapped[list["Follower"]] = relationship(
        "Follower",
        foreign_keys="[Follower.follower_id]",
        back_populates="follower",
        passive_deletes=True
    )

    def __repr__(self):
        return f"User(id={self.id}, username='{self.username}', email='{self.email}')"

    ONLINE_THRESHOLD_SECONDS = 60

    @property
    def is_online(self) -> bool:
        if self.last_seen_at is None:
            return False
        last_seen = self.last_seen_at
        if last_seen.tzinfo is None:
            last_seen = last_seen.replace(tzinfo=datetime.timezone.utc)
        now = datetime.datetime.now(datetime.timezone.utc)
        return (now - last_seen).total_seconds() <= self.ONLINE_THRESHOLD_SECONDS

    def get_following_count(self, session):
        """Get count of users this user follows"""
        return session.query(func.count(Follower.id))\
            .filter(Follower.follower_id == self.id).scalar()

    def get_following_paginated(self, session, page=1, page_size=20):
        """Get paginated list of users being followed"""
        offset = (page - 1) * page_size
        return session.query(Follower)\
            .filter(Follower.follower_id == self.id)\
            .order_by(Follower.created_at.desc())\
            .offset(offset)\
            .limit(page_size)\
            .all()

    def is_following(self, session, user_id):
        """Check if this user follows another user"""
        return session.query(Follower)\
            .filter_by(follower_id=self.id, followed_id=user_id)\
            .first() is not None


class RefreshToken(Base):
    __tablename__ = "refresh_tokens"

    id: Mapped[int] = mapped_column(primary_key=True)
    token_hash: Mapped[str] = mapped_column(String(255), nullable=False, unique=True)
    user_id: Mapped[int] = mapped_column(BigInteger, ForeignKey("users.id"), nullable=False)
    user: Mapped[User] = relationship(back_populates="refresh_tokens")
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    expires_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    revoked: Mapped[bool] = mapped_column(Boolean, nullable=False, server_default='false')


class Follower(Base):
    __tablename__ = "followers"
    __table_args__ = (
        UniqueConstraint("follower_id", "followed_id", name="uq_follower"),
    )

    id: Mapped[int] = mapped_column(primary_key=True)
    follower_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("users.id", ondelete="CASCADE"), nullable=False
    )
    followed_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("users.id", ondelete="CASCADE"), nullable=False
    )
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False, server_default=func.now())
    # Relationships
    follower: Mapped[User] = relationship(foreign_keys=[follower_id], back_populates="following")
    followed: Mapped[User] = relationship(foreign_keys=[followed_id], back_populates="followers")


class UsersLibrary(Base):
    __tablename__ = "users_library"
    __table_args__ = (
        UniqueConstraint("user_id", "name", name="uq_users_library_user_name"),
    )

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    user_id: Mapped[int] = mapped_column(BigInteger, ForeignKey("users.id", ondelete="CASCADE"), nullable=False)
    name: Mapped[str] = mapped_column(String(100), nullable=False)

    books: Mapped[list["UsersLibraryBook"]] = relationship(
        "UsersLibraryBook", back_populates="library", cascade="all, delete-orphan"
    )


class UsersLibraryBook(Base):
    __tablename__ = "users_library_book"

    library_id: Mapped[int] = mapped_column(
        BigInteger, ForeignKey("users_library.id", ondelete="CASCADE"), primary_key=True
    )
    book_id: Mapped[int] = mapped_column(
        BigInteger, primary_key=True
    )

    library: Mapped["UsersLibrary"] = relationship("UsersLibrary", back_populates="books")


class PublicApiKey(Base):
    __tablename__ = "public_api_keys"

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    token_hash: Mapped[str] = mapped_column(String(255), nullable=False, unique=True)
    name: Mapped[str] = mapped_column(String(100), nullable=False)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False, server_default=func.now())
    expires_at: Mapped[datetime.datetime | None] = mapped_column(DateTime, nullable=True)
    last_used_at: Mapped[datetime.datetime | None] = mapped_column(DateTime, nullable=True)
    revoked: Mapped[bool] = mapped_column(Boolean, nullable=False, server_default='false')
