FROM nginx:alpine

RUN rm /etc/nginx/conf.d/default.conf

RUN apk add --no-cache apache2-utils openssl && \
      htpasswd -nb admin elk1234 > /etc/nginx/kibana.htpasswd

RUN mkdir /etc/nginx/certs && \
      openssl req -x509 -newkey rsa:4096 \
          -keyout /etc/nginx/certs/key.pem \
          -out /etc/nginx/certs/cert.pem \
          -sha256 -days 365 -nodes \
          -subj "/C=XX/ST=CZ/L=Prague/O=school42/OU=sombru/CN=localhost"

# Place as a template so the nginx entrypoint runs envsubst on it at startup,
# substituting ${HTTPS_PORT}. Output lands in /etc/nginx/conf.d/nginx.conf.
COPY nginx.conf /etc/nginx/templates/nginx.conf.template