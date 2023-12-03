FROM debian:bullseye

RUN apt-get update \
    && apt-get install \
    -y irssi wget \
    && wget -O /root/image.jpeg https://static.cnews.fr/sites/default/files/styles/image_750_422/public/2023-09-26t211427z_1229151747_rc2kg3azk6r7_rtrmadp_3_google-anniversary-taille1200_6513f7c3611a3.jpg?itok=KiQxfbdI

COPY config /root/.irssi/

ENTRYPOINT [ "tail", "-F", "/dev/null" ]
