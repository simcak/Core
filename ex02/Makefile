NAME	= Bureaucrat
COM		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98

DIR		= ./src
TMP_SRC	= $(shell find $(DIR) -iname "*.cpp")

SRC		= ./src/Bureaucrat.cpp ./src/AForm.cpp ./src/ShrubberyCreationForm.cpp ./src/RobotomyRequestForm.cpp ./src/PresidentialPardonForm.cpp ./src/main.cpp
OBJ		= $(SRC:%.cpp=%.o)

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m
42D		= "------------------------------------------"

%.o: %.cpp
	@$(COM) $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	@printf "$(GREEN)$(42D)\n$(NAME) Compiled!\n$(42D)$(RST)\n"

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@printf "$(RED)$(42D)\nDeleting o-files!\n$(42D)$(RST)\n"

fclean: update_makefile
	@rm -f $(OBJ) $(NAME)
	@printf "$(RED)$(42D)\nDeleting o-files & $(NAME) file\n$(42D)$(RST)\n"

re: fclean all

update_makefile:
	@sed '8d' Makefile > Makefile.tmp
	@awk 'NR==7{print $$0 "\nSRC\t\t= $(TMP_SRC)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

# norminette:
# 	@norminette $(SRC)

party:
	@curl parrot.live

.PHONY: all clean fclean re update_makefile party
