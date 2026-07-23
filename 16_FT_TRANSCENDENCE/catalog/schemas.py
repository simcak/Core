from pydantic import BaseModel, ConfigDict, Field
from datetime import datetime


class AuthorResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    author_name: str


class PublisherResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    publisher_name: str


class BookCategoryResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    category_name: str


class BookTranslationResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    lang: str
    title: str
    description: str | None
    cover_image_filename: str | None
    sample_url: str | None


class ShortBookResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    author: AuthorResponse
    translations: list[BookTranslationResponse]
    price: float
    currency: str
    language_code: str | None
    product_status: str


class BookResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    author: AuthorResponse
    publisher: PublisherResponse | None
    translations: list[BookTranslationResponse]
    categories: list[BookCategoryResponse]
    price: float
    currency: str
    language_code: str | None
    isbn: str | None
    product_status: str


class TranslationInput(BaseModel):
    lang: str
    title: str
    description: str | None = None
    cover_image_filename: str | None = None


class BookCreateRequest(BaseModel):
    author_name: str
    publisher_name: str | None = None
    price: float
    currency: str
    language_code: str | None = None
    isbn: str | None = None
    product_status: str
    translations: list[TranslationInput]
    category_ids: list[int] = []


class BookUpdateRequest(BaseModel):
    author_name: str | None = None
    publisher_name: str | None = None
    price: float | None = None
    currency: str | None = None
    language_code: str | None = None
    isbn: str | None = None
    product_status: str | None = None
    translations: list[TranslationInput] | None = None
    category_ids: list[int] | None = None


class ReviewCreateRequest(BaseModel):
    username: str
    rating: int = Field(ge=1, le=5)
    text: str | None = None


class ReviewResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: int
    user_id: int
    username: str
    rating: int
    text: str | None
    created_at: datetime


class BookReviewsResponse(BaseModel):
    average_rating: float | None
    count: int
    reviews: list[ReviewResponse]
