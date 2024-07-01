# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:18:46 by psimcak           #+#    #+#              #
#    Updated: 2024/07/01 20:51:28 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
FLAGS	= -Wall -Wextra -Werror -pthread
FLAGS	= -Wall -Wextra -pthread

SRC 	= $(shell find ./src -iname "*.c")
OBJ 	= $(SRC:%.c=%.o)

%.o: %.c
		@cc $(FLAGS) -I includes -c $< -o $(<:.c=.o)

all: $(OBJ)
		@cc ${OBJ} -o ${NAME}
		@printf "\033[32m----$(NAME)sophers Compiled!----\033[0m\n"

clean:
		@rm -f $(OBJ)
		@printf "\033[31m----Deleting o-files!----\033[0m\n"

fclean: clean
		@rm -f $(NAME)
		@printf "\033[31m----Deleting o-files & $(NAME)sophers!----\033[0m\n"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party
