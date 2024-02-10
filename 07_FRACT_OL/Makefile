# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peta <peta@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 18:55:21 by psimcak           #+#    #+#              #
#    Updated: 2023/12/02 15:29:52 by peta             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= fract-ol
PATH_TO_LIBRARY = -L minilibx-linux
NAME_OF_ARCHIVE = -l mlx_Linux

# -L minilibx-linux	= path to the library
# -l mlx_Linux		= name of the archive
# gcc *.c -L minilibx-linux -l mlx_Linux -l X11 -l Xext -o fract-ol

all:
		@gcc *.c $(PATH_TO_LIBRARY) $(NAME_OF_ARCHIVE) -l X11 -l Xext -o $(NAME)
		@echo "\033[32m----Fract-ol Compiled!----\e[0m"

mandelbrot: all
		@./$(NAME) mandelbrot
		@echo "\033[32m----MANDELBROT----\e[0m"

julia: all
		@./$(NAME) julia -0.8 0.156
		@echo "\033[32m----JULIA----\e[0m"

fclean:
		@rm -f $(NAME)
		@echo "\033[31m----Deleting fract-ol!----\e[0m"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all fclean re party