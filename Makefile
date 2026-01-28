################################################################################

NAME	= ircserv
CFLAGS	= -Wall -Wextra -Werror -std=c++98
CXX		= c++
DIR		= ./sources ./
OBJDIR	= ./objects

#################################### COLORES ###################################

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

define INFO
	@echo " ______________________________________________________"
	@echo "|     \t$(1)$(2)$(RST)\t       |"
	@echo " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
endef

################################# DEPENDENCIES #################################

T_SRC	= $(shell find $(DIR) -maxdepth 2 -iname "*.cpp")
SRC		= ./sources/classes/Channel.cpp ./sources/classes/Server.cpp ./sources/classes/User.cpp ./sources/commands/cmd_join.cpp ./sources/commands/cmd_nickname.cpp ./sources/commands/cmd_pass.cpp ./sources/commands/cmd_pong.cpp ./sources/commands/cmd_quit.cpp ./sources/commands/cmd_receive_msg.cpp ./sources/commands/cmd_send_msg.cpp ./sources/commands/cmd_user.cpp ./sources/controllers/ServerController.cpp ./sources/utils/utils.cpp ./main.cpp

OBJ	= $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))
DEP	= $(OBJ:.o=.d)

#################################### BUILD #####################################

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	$(call INFO,\t$(GREEN),"${NAME} Compiled!"\t)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	$(call INFO,\t$(RED),"Deleting o-files!"\t)

fclean:
	@rm -rf $(OBJDIR) $(NAME)
	$(call INFO,$(RED),"Deleting o-files \&\& compiled file!")

re: update_makefile fclean all

update_makefile:
	@sed '24d' Makefile > Makefile.tmp
	@awk 'NR==23{print $$0 "\nSRC\t\t= $(T_SRC)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

-include $(DEP)

.PHONY: all clean fclean re

################################################################################
