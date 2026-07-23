import os
from pydantic import SecretStr
import logging

logging.basicConfig(

    level=logging.INFO,

    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",

    datefmt="%Y-%m-%d %H:%M:%S",

)

logger = logging.getLogger("auth")


class Settings:
    def __init__(self) -> None:
        self.secret_key: SecretStr = SecretStr(os.getenv("SECRET_KEY", "dev-secret"))
        self.algorithm: str = os.getenv("ALGORITHM", "HS256")
        self.access_token_expires_minutes: int = int(os.getenv("ACCESS_TOKEN_EXPIRES_MINUTES", "15"))
        self.refresh_token_expires_days: int = int(os.getenv("REFRESH_TOKEN_EXPIRES_DAYS", "7"))
        self.cookie_secure: bool = os.getenv("COOKIE_SECURE", "false").lower() == "true"


class OauthSettings:
    def __init__(self) -> None:
        self.uid: str = os.getenv("42_UID_KEY", "")
        self.secret_key: str = os.getenv("42_API_KEY", "")
        self.oauth_42_redirect_uri: str | None = os.getenv("OAUTH_42_REDIRECT_URI")
        self.oauth_frontend_redirect_uri: str = os.getenv(
            "OAUTH_FRONTEND_REDIRECT_URI",
            "/",
        )


settings = Settings()
oauth_settings = OauthSettings()
