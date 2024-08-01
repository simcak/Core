# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 14:51:37 by psimcak           #+#    #+#              #
#    Updated: 2024/07/30 16:09:26 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = phonebook
COM     = c++
FLAGS   = -Wall -Wextra -Werror -std=c++98

DIR     = .
SRC_ILL = $(shell find $(DIR) -iname "*.cpp")

SRC		= ./main.cpp ./src/PhoneBook.cpp ./src/safeGetline.cpp
OBJ     = $(SRC:%.cpp=%.o)

RED     = \033[31m
GREEN   = \033[32m
RST     = \033[0m

%.o: %.cpp
	@$(COM) $(FLAGS) -c $< -o $(<:.cpp=.o)

all: update_makefile $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

update_makefile:
	@sed '20d' Makefile > Makefile.tmp
	@awk 'NR==19{print $$0 "\nSRC\t\t= $(SRC_ILL)"; next}1' Makefile.tmp > Makefile
	@rm Makefile.tmp

party:
	@curl parrot.live

.PHONY: all clean fclean re update_makefile party
