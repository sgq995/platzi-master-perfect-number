FROM gcc

COPY ./src /usr/src

WORKDIR /usr/src

RUN gcc -o perfect main.c

ENTRYPOINT ["./perfect"]
