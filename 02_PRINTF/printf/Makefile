# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 11:40:46 by psimcak           #+#    #+#              #
#    Updated: 2023/08/30 13:39:48 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
FLAGS	= -Wall -Wextra -Werror
SRC 	= $(shell find ./src -iname "*.c")
OBJ 	= $(SRC:%.c=%.o)

%.o: %.c
	cc $(FLAGS) -I. -c $< -o $@

all: $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

