# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 17:19:28 by nandroso          #+#    #+#              #
#    Updated: 2023/09/01 19:43:38 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
FLAGS	= -Wall -Wextra -Werror
SRC 	= $(shell find . -iname "*.c")
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
