# docker build -t task .
# docker run --rm -it task /bin/bash
# ./task
# gcc -Wall task.c -o task

FROM debian:bullseye-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

COPY task.c .

