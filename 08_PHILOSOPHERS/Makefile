# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:18:46 by psimcak           #+#    #+#              #
#    Updated: 2024/06/18 14:24:18 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philosophers
FLAGS	= -Wall -Wextra -Werror -g

SRC 	= $(shell find ./src -iname "*.c")
OBJ 	= $(SRC:%.c=%.o)

%.o: %.c
		@cc $(FLAGS) -I includes -c $< -o $(<:.c=.o)

all: $(OBJ)
		@cc ${OBJ} -o ${NAME}
		@echo "\033[32m----Push-Swap Compiled!----\e[0m"

clean:
		@rm -f $(OBJ)
		@echo "\033[31m----Deleting o-files!----\e[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m----Deleting o-files & $(NAME)!----\e[0m"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party
