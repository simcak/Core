################################################################################

NAME	= ircserv
CFLAGS	= -Wall -Wextra -Werror -std=c++98 $(DEBUG_FLAG)
CXX		= c++
DIR		= .
OBJDIR	= ./objects

#################################### COLORES ###################################

RED		= \033[31m
GREEN	= \033[32m
RSET	= \033[0m

define INFO
	@echo " __________________________________________________"
	@echo "|         $(1)$(2)$(RSET)           |"
	@echo " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
endef

################################# DEPENDENCIES #################################

T_SRC	= $(shell find $(DIR) -iname "*.cpp")
SRC		= ./main.cpp ./srcs/Channel.cpp ./srcs/Message.cpp ./srcs/Server.cpp ./srcs/User.cpp ./srcs/utils.cpp ./srcs/cmds/Quit.cpp ./srcs/cmds/User.cpp ./srcs/cmds/Nick.cpp ./srcs/cmds/Pass.cpp ./srcs/cmds/Kick.cpp ./srcs/cmds/Invite.cpp ./srcs/cmds/Topic.cpp ./srcs/cmds/Part.cpp ./srcs/cmds/PrivMsg.cpp ./srcs/cmds/Mode.cpp ./srcs/cmds/Names.cpp ./srcs/cmds/List.cpp ./srcs/cmds/Who.cpp ./srcs/cmds/Join.cpp

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
	$(call INFO,$(RED)," Deleting o-files \&\& ircserv! ")

re: update_makefile fclean all

update_makefile:
	@sed '24d' Makefile > Makefile.tmp
	@awk 'NR==23{print $$0 "\nSRC\t\t= $(T_SRC)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

-include $(DEP)

.PHONY: all clean fclean re

################################################################################
