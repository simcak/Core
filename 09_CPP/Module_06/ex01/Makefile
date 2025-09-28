NAME	= Serialization
COM		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98

DIR		= ./src
T_SRC	= $(shell find $(DIR) -iname "*.cpp")

SRC		= 
OBJ		= $(SRC:%.cpp=%.o)

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

define INFO
	@echo "======================================================"
	@echo "======\t$(1)$(2)$(RST)\t======"
	@echo "======================================================"
endef

##################################### Rules ####################################
%.o: %.cpp
	@$(COM) $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	$(call INFO,\t$(GREEN),"${NAME} Compiled!")

all: $(NAME)

clean: update_makefile
	@rm -f $(OBJ)
	$(call INFO,\t$(RED),"Deleting o-files!"\t)

fclean: update_makefile
	@rm -f $(OBJ) $(NAME)
	$(call INFO,$(RED),"Deleting o-files \&\& compiled file!")

re: fclean all

update_makefile:
	@sed '8d' Makefile > Makefile.tmp
	@awk 'NR==7{print $$0 "\nSRC\t\t= $(T_SRC)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

# norminette:
# 	@norminette $(SRC)

party: fclean
	@curl parrot.live

.PHONY: all clean fclean re update_makefile party
