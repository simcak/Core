################################################
## ARGUMENTS

NAME = ircserv
CFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++
OBJDIR = .objects
################################################
## COLORS

# Reset
END_COLOR	= \033[0m       # Text Reset

# Regular Colors
BLACK	= \033[0;30m        # Black
RED		= \033[0;31m          # Red
GREEN	= \033[0;32m        # Green
YELLOW	= \033[0;33m       # Yellow
BLUE	= \033[0;34m         # Blue
PURPLE	= \033[0;35m       # Purple
CYAN	= \033[0;36m         # Cyan
WHITE	= \033[0;37m        # White

################################################
## SOURCES

SRC	= 	main.cpp \
		sources/classes/Server.cpp \
		sources/classes/User.cpp \
		sources/classes/Channel.cpp \
		sources/controllers/ServerController.cpp \
		sources/utils/utils.cpp \
		sources/commands/cmd_nickname.cpp \
		sources/commands/cmd_user.cpp \
		sources/commands/cmd_join.cpp \
		sources/commands/cmd_pass.cpp \
		sources/commands/cmd_receive_msg.cpp \
		sources/commands/cmd_send_msg.cpp \
		sources/commands/cmd_pong.cpp \
		sources/commands/cmd_quit.cpp \
 


HEADER	=	sources/headers/ft_irc.hpp \
			sources/headers/Server.hpp \
			sources/headers/User.hpp \
			sources/headers/Channel.hpp \

OBJ	= $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))
DEP	= $(OBJ:.o=.d)
################################################
## RULES

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) COMPILED!! $(END_COLOR)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
