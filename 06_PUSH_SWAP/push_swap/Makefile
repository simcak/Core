# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 17:01:57 by psimcak           #+#    #+#              #
#    Updated: 2023/10/10 17:07:07 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= push_swap
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
		@echo "\033[31m----Deleting object files!----\e[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m----Deleting o-files & pipex!----\e[0m"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party