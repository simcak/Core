# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 14:51:37 by psimcak           #+#    #+#              #
#    Updated: 2024/10/19 16:41:59 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = phonebook
COM     = c++
FLAGS   = -Wall -Wextra -Werror -std=c++98

SRC		= ./main.cpp ./src/PhoneBook.cpp ./src/safeGetline.cpp
OBJ     = $(SRC:%.cpp=%.o)

# find . -iname "*.cpp" -print0 | xargs -0 echo

RED     = \033[31m
GREEN   = \033[32m
RST     = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

%.o: %.cpp
	@$(COM) $(FLAGS) -c $< -o $(<:.cpp=.o)

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

party:
	@curl parrot.live

.PHONY: all clean fclean re party
