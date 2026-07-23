# health
curl -i http://localhost:8080/api/health

# register (example)
EMAIL="ci$(date +%s)@example.com"
PASSWORD='Password1!'
curl -i -X POST -H 'Content-Type: application/json' \
  -d "{\"email\":\"$EMAIL\",\"password\":\"$PASSWORD\",\"username\":\"citest\"}" \
  http://localhost:8080/auth/register

# login (saves cookies)
curl -i -X POST -H 'Content-Type: application/json' \
  -d "{\"email\":\"$EMAIL\",\"password\":\"$PASSWORD\"}" -c /tmp/auth_cookies.txt \
  http://localhost:8080/auth/login