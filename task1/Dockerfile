# docker build -t task .
# docker run --rm -it task /bin/bash
# ./task

FROM debian:bullseye-slim

WORKDIR /app

# Встановлюємо необхідні пакети: gcc, rwho, more (через util-linux)
RUN apt-get update && apt-get install -y \
    gcc \
    util-linux \
    procps \
    && rm -rf /var/lib/apt/lists/*

COPY task.c .

# Скомпілювати з попередженнями
RUN gcc -Wall -g task.c -o task
