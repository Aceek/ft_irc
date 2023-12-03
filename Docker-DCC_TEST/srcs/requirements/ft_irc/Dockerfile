FROM debian:bullseye

RUN apt-get update \
    && apt-get install \
    -y irssi git build-essential \
    && git clone https://github.com/Aceek/ft_irc.git \
    && cd ft_irc && make

# Correction
#COPY PATH_TO_ft_irc_PROJECT /ft_irc/
#RUN apt-get update \
#    && apt-get install \
#    -y build-essential \
#    && cd ft_irc && make

WORKDIR /ft_irc

ENTRYPOINT [ "./ircserv", "6139", "password" ]
