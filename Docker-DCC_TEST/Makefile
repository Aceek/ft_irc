# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 21:04:20 by rlouvrie          #+#    #+#              #
#    Updated: 2023/12/05 18:17:09 by rlouvrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPOSE_FILE := srcs/docker-compose.yaml

COMPOSE := docker compose -f $(COMPOSE_FILE)

all: up

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
	$(COMPOSE) down --volumes
	docker system prune -a -f --volumes


.PHONY: all up stop down ps logs ssh validate restart clean
