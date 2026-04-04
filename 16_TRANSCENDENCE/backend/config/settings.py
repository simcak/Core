# config/settings.py

INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",

    "rest_framework",

    "apps.users",
    "apps.books",
    "apps.library",
    "apps.playback",
]

AUTH_USER_MODEL = "users.User"
