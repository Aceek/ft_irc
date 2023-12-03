FROM debian:bullseye

RUN apt-get update \
    && apt-get install \
    -y irssi

COPY config /root/.irssi/

ENTRYPOINT [ "tail", "-F", "/dev/null" ]
