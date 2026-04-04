# apps/books/models.py
from django.db import models


class Genre(models.Model):
    name = models.CharField(max_length=64, unique=True)
    slug = models.SlugField(unique=True)

    def __str__(self):
        return self.name


class Author(models.Model):
    name = models.CharField(max_length=255)
    slug = models.SlugField(unique=True)

    def __str__(self):
        return self.name


class Book(models.Model):
    title = models.CharField(max_length=255)
    slug = models.SlugField(unique=True)
    author = models.ForeignKey(Author, on_delete=models.PROTECT, related_name="books")
    genres = models.ManyToManyField(Genre, related_name="books", blank=True)

    cover_url = models.URLField(blank=True, default="")
    description = models.TextField(blank=True, default="")
    duration_seconds = models.PositiveIntegerField(default=0)
    language = models.CharField(max_length=32, default="en")
    rating_avg = models.DecimalField(max_digits=3, decimal_places=2, default=0)
    price_cents = models.PositiveIntegerField(default=0)
    sample_seconds = models.PositiveIntegerField(default=300)

    is_published = models.BooleanField(default=True)
    is_featured = models.BooleanField(default=False)
    is_bestseller = models.BooleanField(default=False)

    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.title