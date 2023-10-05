# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peta <peta@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/28 17:08:55 by psimcak           #+#    #+#              #
#    Updated: 2023/10/05 14:50:28 by peta             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= pipex
FLAGS	= -Wall -Wextra -Werror -g

# Finds all .c files in the ./src directory and its subdirectories.
SRC 	= $(shell find ./src -iname "*.c")

# Substitutes .c extensions for .o in the SRC 
# Creates list of object files
OBJ 	= $(SRC:%.c=%.o)

# Pattern rule for building .o files from .c files.
%.o: %.c
		@cc $(FLAGS) -I includes -c $< -o $(<:.c=.o)
# For example, if $< is srcs/pipex.c, then $(<:.c=.o) would be srcs/pipex.o.
# The -I flag tells the compiler to add "includes" to the list of directories \
searched for header files.

# The default rule that builds everything.
all: $(OBJ)
		@cc ${OBJ} -o ${NAME}
		@echo "\033[32m----Pipex Compiled!----\e[0m"

# Rules for cleaning up the build.
clean:
		@rm -f $(OBJ)
		@echo "\033[31m----Deleting object files!----\e[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m----Deleting o-files & pipex!----\e[0m"

re: 	fclean all

# just 4 fun
party:
		@curl parrot.live

# Specifies that the listed names are not file names.
.PHONY: all clean fclean re party

