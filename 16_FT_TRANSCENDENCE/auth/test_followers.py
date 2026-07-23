import pytest
import datetime
from sqlalchemy import create_engine, event
from sqlalchemy.orm import sessionmaker
from sqlalchemy.pool import StaticPool

from auth.models import Base, User, Follower, Role


@pytest.fixture
def db_session():
    """Create an in-memory SQLite database for testing"""
    engine = create_engine(
        "sqlite:///:memory:",
        connect_args={"check_same_thread": False},
        poolclass=StaticPool
    )

    # Enable foreign key support in SQLite
    def enable_foreign_keys(dbapi_connection, connection_record):
        cursor = dbapi_connection.cursor()
        cursor.execute("PRAGMA foreign_keys=ON")
        cursor.close()

    event.listen(engine, "connect", enable_foreign_keys)

    Base.metadata.create_all(engine)

    Session = sessionmaker(bind=engine)
    session = Session()

    # Create default role
    role = Role(role_name="user")
    session.add(role)
    session.commit()

    yield session
    session.close()


@pytest.fixture
def sample_users(db_session):
    """Create sample users for testing"""
    now = datetime.datetime.now()

    user1 = User(
        username="alice",
        email="alice@test.com",
        password_hash="hash1",
        role_id=1,
        created_at=now,
        updated_at=now
    )
    user2 = User(
        username="bob",
        email="bob@test.com",
        password_hash="hash2",
        role_id=1,
        created_at=now,
        updated_at=now
    )
    user3 = User(
        username="charlie",
        email="charlie@test.com",
        password_hash="hash3",
        role_id=1,
        created_at=now,
        updated_at=now
    )

    db_session.add_all([user1, user2, user3])
    db_session.commit()

    return user1, user2, user3


class TestFollowerModel:
    """Test the Follower model and relationships"""

    def test_follower_defaults_created_at(self, db_session, sample_users):
        """Test follower rows receive a timestamp when created without one"""
        current_user, target_user, _ = sample_users

        follower = Follower(
            follower_id=current_user.id,
            followed_id=target_user.id,
        )
        db_session.add(follower)
        db_session.commit()

        persisted_follower = db_session.query(Follower).filter_by(
            follower_id=current_user.id,
            followed_id=target_user.id,
        ).one()

        assert persisted_follower.created_at is not None

    def test_create_follower(self, db_session, sample_users):
        """Test creating a follower relationship"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        follower = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(follower)
        db_session.commit()

        # Verify the relationship was created
        assert follower.id is not None
        assert follower.follower_id == user1.id
        assert follower.followed_id == user2.id

    def test_unique_constraint(self, db_session, sample_users):
        """Test that duplicate follows are prevented"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        # Create first follower
        f1 = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(f1)
        db_session.commit()

        # Try to create duplicate
        f2 = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(f2)

        with pytest.raises(Exception):  # IntegrityError
            db_session.commit()

    @pytest.mark.skip(reason="SQLite has limitations with cascade deletes in-memory. Test with PostgreSQL.")
    def test_cascade_delete(self, db_session, sample_users):
        """Test that follower relationships are deleted when user is deleted"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        # Create follower relationship
        follower = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(follower)
        db_session.commit()

        # Delete user1
        db_session.delete(user1)
        db_session.commit()

        # Verify follower was deleted
        remaining = db_session.query(Follower).filter_by(follower_id=user1.id).first()
        assert remaining is None


class TestUserFollowerMethods:
    """Test the follower-related methods on User model"""

    def test_is_following_true(self, db_session, sample_users):
        """Test is_following returns True when user follows another"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        follower = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(follower)
        db_session.commit()

        assert user1.is_following(db_session, user2.id)

    def test_is_following_false(self, db_session, sample_users):
        """Test is_following returns False when user doesn't follow"""
        user1, user2, _ = sample_users

        assert not user1.is_following(db_session, user2.id)

    def test_get_following_count(self, db_session, sample_users):
        """Test counting users being followed"""
        user1, user2, user3 = sample_users
        now = datetime.datetime.now()

        # user1 follows user2 and user3
        f1 = Follower(follower_id=user1.id, followed_id=user2.id, created_at=now)
        f2 = Follower(follower_id=user1.id, followed_id=user3.id, created_at=now)
        db_session.add_all([f1, f2])
        db_session.commit()

        count = user1.get_following_count(db_session)
        assert count == 2

    def test_get_following_count_empty(self, db_session, sample_users):
        """Test counting when user follows no one"""
        user1, _, _ = sample_users

        count = user1.get_following_count(db_session)
        assert count == 0

    def test_get_following_paginated(self, db_session, sample_users):
        """Test paginated list of followed users"""
        user1, user2, user3 = sample_users
        now = datetime.datetime.now()

        # user1 follows user2 and user3
        f1 = Follower(follower_id=user1.id, followed_id=user2.id, created_at=now)
        f2 = Follower(follower_id=user1.id, followed_id=user3.id, created_at=now)
        db_session.add_all([f1, f2])
        db_session.commit()

        # Get first page
        page1 = user1.get_following_paginated(db_session, page=1, page_size=1)
        assert len(page1) == 1

        # Get second page
        page2 = user1.get_following_paginated(db_session, page=2, page_size=1)
        assert len(page2) == 1

        # Verify they're different
        assert page1[0].followed_id != page2[0].followed_id

    def test_bidirectional_relationships(self, db_session, sample_users):
        """Test that bidirectional relationships work correctly"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        # user1 follows user2
        follower = Follower(
            follower_id=user1.id,
            followed_id=user2.id,
            created_at=now
        )
        db_session.add(follower)
        db_session.commit()

        # Refresh to load relationships
        db_session.refresh(user1)
        db_session.refresh(user2)

        # user1.following should include the relationship
        assert len(user1.following) == 1
        assert user1.following[0].followed_id == user2.id

        # user2.followers should include the relationship
        assert len(user2.followers) == 1
        assert user2.followers[0].follower_id == user1.id


class TestFollowerRelationships:
    """Test complex follower scenarios"""

    def test_mutual_follows(self, db_session, sample_users):
        """Test when two users follow each other"""
        user1, user2, _ = sample_users
        now = datetime.datetime.now()

        # Both follow each other
        f1 = Follower(follower_id=user1.id, followed_id=user2.id, created_at=now)
        f2 = Follower(follower_id=user2.id, followed_id=user1.id, created_at=now)
        db_session.add_all([f1, f2])
        db_session.commit()

        assert user1.is_following(db_session, user2.id)
        assert user2.is_following(db_session, user1.id)

    def test_follow_chain(self, db_session, sample_users):
        """Test a chain of follows: A->B->C"""
        user1, user2, user3 = sample_users
        now = datetime.datetime.now()

        # A follows B, B follows C
        f1 = Follower(follower_id=user1.id, followed_id=user2.id, created_at=now)
        f2 = Follower(follower_id=user2.id, followed_id=user3.id, created_at=now)
        db_session.add_all([f1, f2])
        db_session.commit()

        assert user1.is_following(db_session, user2.id)
        assert user2.is_following(db_session, user3.id)
        assert not user1.is_following(db_session, user3.id)  # A doesn't follow C
