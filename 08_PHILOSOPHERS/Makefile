# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:18:46 by psimcak           #+#    #+#              #
#    Updated: 2024/07/26 17:16:21 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
FLAGS	= -Wall -Wextra -Werror -pthread

SRC 	= $(shell find ./src -iname "*.c")
OBJ 	= $(SRC:%.c=%.o)

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

%.o: %.c
		@cc $(FLAGS) -I includes -c $< -o $(<:.c=.o)

all: $(OBJ)
		@cc ${OBJ} -o ${NAME}
		@printf "$(GREEN)----$(NAME)sophers Compiled!----$(RST)\n"

clean:
		@rm -f $(OBJ)
		@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
		@rm -f $(NAME)
		@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party
