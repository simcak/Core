# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peta <peta@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 17:01:57 by psimcak           #+#    #+#              #
#    Updated: 2023/10/27 17:26:24 by peta             ###   ########.fr        #
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
		@echo "\033[31m----Deleting o-files!----\e[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m----Deleting o-files & push_swap!----\e[0m"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party