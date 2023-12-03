# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 21:04:20 by rlouvrie          #+#    #+#              #
#    Updated: 2023/12/03 21:06:02 by rlouvrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPOSE_FILE := srcs/docker-compose.yaml

COMPOSE := docker-compose -f $(COMPOSE_FILE)

all: build up

build:
	$(COMPOSE) build

up:
	$(COMPOSE) up -d

stop:
	$(COMPOSE) stop

down:
	$(COMPOSE) down

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs

ssh:
	$(COMPOSE) exec $(service) /bin/bash

validate:
	$(COMPOSE) config --quiet

restart:
	$(COMPOSE) up -d --no-deps --build $(service)

clean:
	$(COMPOSE) down -v
	$(COMPOSE) down --volumes
	docker system prune -a -f --volumes


.PHONY: all build up up-fg stop down ps logs ssh validate restart clean