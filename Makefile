CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp server.cpp client.cpp channel.cpp #command.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = ft_irc

HEADER = server.hpp client.hpp
INCLUDES = -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all