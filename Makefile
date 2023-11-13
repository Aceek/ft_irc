# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 04:05:12 by pbeheyt           #+#    #+#              #
#    Updated: 2023/11/13 07:09:41 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := c++
FLAGS   := -Wall -Wextra -Werror -std=c++98 -g

SRCS    := $(wildcard srcs/*.cpp) $(wildcard srcs/*/*.cpp)
OBJS    := $(patsubst srcs/%.cpp,obj/%.o,$(SRCS))
NAME    := ft_irc

HEADER  := $(wildcard srcs/*.hpp) $(wildcard srcs/*/*.hpp)
INCLUDES := -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

obj/%.o: srcs/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all
