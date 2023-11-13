# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 04:05:12 by pbeheyt           #+#    #+#              #
#    Updated: 2023/11/13 12:26:44 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := c++
FLAGS   := -Wall -Wextra -Werror -std=c++98 -g

SRCS    := $(wildcard srcs/*.cpp) $(wildcard srcs/*/*.cpp)
OBJS    := $(patsubst srcs/%.cpp,obj/%.o,$(SRCS))
NAME    := ft_irc

HEADER  := $(wildcard srcs/*.hpp) $(wildcard srcs/*/*.hpp)
INCLUDES := -I.

# Colors
GREEN	:= \033[0;32m
RED		:= \033[0;31m
RESET	:= \033[0m
BOLD	:= \033[1m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ -o $@
	@echo "$(GREEN)$(BOLD)Build successful: $(NAME)$(RESET)"

obj/%.o: srcs/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)$(BOLD)Compiled: $<$(RESET)"

clean:
	@rm -rf obj
	@echo "$(RED)$(BOLD)Cleaned: $(NAME)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(BOLD)Removed: $(NAME)$(RESET)"

re: fclean all
