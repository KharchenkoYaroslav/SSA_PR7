# docker build -t task .
# docker run --rm -it task /bin/bash

# gcc -g task.c -o task -lm
# su testuser
# cat test.c
# exit
# ./task 
# su testuser
# cat test.c

FROM debian:bullseye-slim


WORKDIR /app

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*


COPY task.c .
COPY test.c .

RUN chmod 600 test.c
RUN useradd -m testuser




