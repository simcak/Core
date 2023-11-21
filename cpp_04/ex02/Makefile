SRCS			= main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp
OBJS			= $(SRCS:.cpp=.o)
CPP				= c++
RM				= rm -f
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98
NAME			= FragTrap
MAGENTA			= "\033[35m"
GREEN			= "\033[32m"
RED				= "\033[31m"
RESET			= "\033[0m"

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJS)
				@echo $(GREEN)"+-+-+-+-+-+-+-+-+ "$(RESET)
				@echo $(GREEN)"|C|o|m|p|i|l|e|d| "$(RESET)
				@echo $(GREEN)"+-+-+-+-+-+-+-+-+ "$(RESET)

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@echo $(RED)"+-+-+-+-+-+-+-+ "$(RESET)
				@echo $(RED)"|C|l|e|a|n|e|d| "$(RESET)
				@echo $(RED)"+-+-+-+-+-+-+-+ "$(RESET)

re:				fclean $(NAME)

.PHONY:			all clean fclean re