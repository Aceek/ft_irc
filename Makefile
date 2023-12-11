CC      := c++
FLAGS   := -Wall -Wextra -Werror -std=c++98 -g

# List source files by directory
BOT_SRCS      := bot.cpp bot_accessors.cpp bot_utils.cpp
CHANNEL_SRCS  := channel.cpp channel_accessors.cpp channel_utils.cpp
CLIENT_SRCS   := client.cpp client_accessors.cpp client_utlis.cpp
COMMAND_SRCS  := CAP.cpp command.cpp command_accessors.cpp command_utlis.cpp \
                 HELP.cpp INVITE.cpp JOIN.cpp KICK.cpp MODE.cpp NICK.cpp \
                 NOTICE.cpp PART.cpp PASS.cpp PONG.cpp PRIVMSG.cpp QUIT.cpp \
                 TOPIC.cpp USER.cpp
SERVER_SRCS   := server.cpp server_accessors.cpp server_utlis.cpp
SERVERREPLY_SRCS := ServerReply.cpp serverReply_auth.cpp serverReply_channel.cpp serverReply_output.cpp
UTILS_SRCS    := utils.cpp
MAIN_SRC      := main.cpp

# Create a path for each source file
SRCS := $(addprefix srcs/,$(MAIN_SRC)) \
        $(addprefix srcs/bot/,$(BOT_SRCS)) \
        $(addprefix srcs/channel/,$(CHANNEL_SRCS)) \
        $(addprefix srcs/client/,$(CLIENT_SRCS)) \
        $(addprefix srcs/command/,$(COMMAND_SRCS)) \
        $(addprefix srcs/server/,$(SERVER_SRCS)) \
        $(addprefix srcs/serverReply/,$(SERVERREPLY_SRCS)) \
        $(addprefix srcs/utils/,$(UTILS_SRCS))

OBJS := $(SRCS:srcs/%.cpp=obj/%.o)
NAME := ircserv

# List header files explicitly
HEADER := srcs/bot/bot.hpp \
          srcs/channel/channel.hpp \
          srcs/client/client.hpp \
          srcs/command/command.hpp \
          srcs/server/server.hpp \
          srcs/serverReply/serverReply.hpp \
          srcs/utils/utils.hpp
INCLUDES := -Isrcs -I.

# Colors
GREEN   := \033[0;32m
RED     := \033[0;31m
RESET   := \033[0m
BOLD    := \033[1m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@
	@echo "$(GREEN)$(BOLD)Build successful: $(NAME)$(RESET)"

# Compile source files into objects
$(OBJS): obj/%.o : srcs/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -rf obj
	@echo "$(RED)Cleaned object files$(RESET)"

fclean: clean
	@echo "$(RED)Full Cleaning...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
