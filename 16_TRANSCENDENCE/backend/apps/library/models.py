# apps/library/models.py
from django.conf import settings
from django.db import models
from apps.books.models import Book


class Shelf(models.Model):
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE, related_name="shelves")
    name = models.CharField(max_length=80)
    color = models.CharField(max_length=16, blank=True, default="")
    position = models.PositiveIntegerField(default=0)
    is_system = models.BooleanField(default=False)  # e.g. Top, Wishlist, Unfinished

    class Meta:
        unique_together = ("user", "name")
        ordering = ["position", "id"]

    def __str__(self):
        return f"{self.user_id}:{self.name}"


class LibraryItem(models.Model):
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE, related_name="library_items")
    book = models.ForeignKey(Book, on_delete=models.CASCADE, related_name="library_items")
    shelf = models.ForeignKey(Shelf, on_delete=models.SET_NULL, null=True, blank=True, related_name="items")
    position = models.PositiveIntegerField(default=0)

    is_owned = models.BooleanField(default=False)
    is_wishlist = models.BooleanField(default=False)

    added_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        unique_together = ("user", "book")
        ordering = ["position", "id"]