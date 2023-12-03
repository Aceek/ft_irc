FROM debian:bullseye

RUN apt-get update \
    && apt-get install \
    -y irssi git build-essential \
    && git clone https://github.com/Aceek/ft_irc.git \
    && cd ft_irc && make

WORKDIR /ft_irc

ENTRYPOINT [ "./ft_irc", "6139", "password" ]
