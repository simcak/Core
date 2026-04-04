# apps/playback/models.py
from django.conf import settings
from django.db import models
from apps.books.models import Book


class PlaybackProgress(models.Model):
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE, related_name="playback_progress")
    book = models.ForeignKey(Book, on_delete=models.CASCADE, related_name="playback_progress")
    current_seconds = models.PositiveIntegerField(default=0)
    completed = models.BooleanField(default=False)
    last_listened_at = models.DateTimeField(auto_now=True)

    class Meta:
        unique_together = ("user", "book")