from models import Role, User, Follower
from database import get_db
from sqlalchemy import select
from sqlalchemy.orm import Session
from utils import hash_password
from faker import Faker
import random

fake = Faker(["cz_CZ", "en_US"])


def seed(db: Session):
    if db.query(Role).count() == 0:
        db.add_all(
            [
                Role(role_name="admin"),
                Role(role_name="user"),
                Role(role_name="author"),
                Role(role_name="guest"),
            ]
        )
    db.flush()
    user_role = db.execute(select(Role).where(Role.role_name == "user")).scalar_one()
    if db.query(User).count() == 0:
        for _ in range(25):
            password_hash = hash_password("password123")  # ONLY FOR SEEDING PURPOSES
            user = User(
                username=fake.user_name(),
                email=fake.email(),
                password_hash=password_hash,
                role_id=user_role.id,
                first_name=fake.first_name(),
                last_name=fake.last_name(),
                phone=fake.phone_number(),
                last_login_at=fake.date_time_between(start_date="-1y", end_date="now"),
                email_verified=True,
                email_verified_at=fake.date_time_between(
                    start_date="-1y", end_date="now"
                ),
                created_at=fake.date_time_between(start_date="-1y", end_date="now"),
                updated_at=fake.date_time_between(start_date="-1y", end_date="now"),
            )
            db.add(user)
    db.commit()

    # Seed follower relationships
    if db.query(Follower).count() == 0:
        users = db.query(User).all()
        if len(users) > 1:
            for user in users:
                # Each user follows 2-5 random other users
                num_to_follow = random.randint(2, min(5, len(users) - 1))
                users_to_follow = random.sample(
                    [u for u in users if u.id != user.id],
                    num_to_follow
                )
                for followed_user in users_to_follow:
                    follower = Follower(
                        follower_id=user.id,
                        followed_id=followed_user.id,
                        created_at=fake.date_time_between(start_date="-1y", end_date="now")
                    )
                    db.add(follower)
        db.commit()

    # Seed admin user
    admin_role = db.execute(select(Role).where(Role.role_name == "admin")).scalar_one()
    if not db.query(User).filter(User.username == "hal").first():
        admin_user = User(
            username="hal",
            email="hal@email.com",
            password_hash=hash_password("controller123"),
            role_id=admin_role.id,
            first_name="HAL",
            last_name="9000",
            phone="+420 123 456 789",
            last_login_at=fake.date_time_between(start_date="-1y", end_date="now"),
            email_verified=True,
            email_verified_at=fake.date_time_between(start_date="-1y", end_date="now"),
            created_at=fake.date_time_between(start_date="-1y", end_date="now"),
            updated_at=fake.date_time_between(start_date="-1y", end_date="now"),
        )
        db.add(admin_user)
        db.commit()


if __name__ == "__main__":
    db = next(get_db())
    seed(db)
