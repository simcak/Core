# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 16:02:27 by psimcak           #+#    #+#              #
#    Updated: 2024/09/25 17:18:39 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = gnl
COM     = cc
FLAGS   = -Wall -Wextra -Werror -D BUFFER_SIZE=42

DIR     = .
SRC_ILL = $(shell find $(DIR) -iname "*.c")

SRC		= ./get_next_line.c
OBJ     = $(SRC:%.c=%.o)

RED     = \033[31m
GREEN   = \033[32m
RST     = \033[0m

%.o: %.c
	@$(COM) $(FLAGS) -c $< -o $(<:.c=.o)

all: update_makefile $(OBJ)
	@$(COM) $(OBJ) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean:
	@rm -f $(OBJ)
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

# **************************************************************************** #
