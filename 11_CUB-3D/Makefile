# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 13:49:49 by psimcak           #+#    #+#              #
#    Updated: 2024/10/29 13:52:06 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
COM		= cc
FLAGS	= -Wall -Wextra -Werror

SRC		=
OBJ		= $(SRC:%.c=%.o)

# find . -iname "*.c" -print0 | xargs -0 echo

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

%.o: %.c
	@$(COM) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

.PHONY: all clean fclean re
