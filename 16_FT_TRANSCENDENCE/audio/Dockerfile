FROM  python:3.12-alpine
ENV PYTHONUNBUFFERED=1
WORKDIR /app

COPY requirements.txt ./requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# COPY auth.py ./auth.py
COPY jwt_handler.py ./jwt_handler.py
COPY database.py ./database.py
COPY migrations ./migrations
COPY models.py ./models.py
COPY router.py ./router.py
COPY public_api.py ./public_api.py
COPY seed.py ./seed.py
COPY schemas.py ./schemas.py
COPY storage.py ./storage.py

CMD ["uvicorn", "router:app", "--host", "0.0.0.0", "--port", "8000"]
