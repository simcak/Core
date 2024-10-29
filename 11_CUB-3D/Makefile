# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 13:49:49 by psimcak           #+#    #+#              #
#    Updated: 2024/10/29 19:07:40 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
COM			= cc
FLAGS		= -Wall -Wextra -Werror
APPLE_FLAGS	= -framework OpenGL -framework Cocoa -framework IOKit

SRC		=./algorithm/main.c ./MLX42/build/CMakeFiles/3.27.1/CompilerIdC/CMakeCCompilerId.c ./MLX42/build/mlx_frag_shader.c ./MLX42/build/mlx_vert_shader.c ./MLX42/lib/glad/glad.c ./MLX42/lib/png/lodepng.c ./MLX42/src/font/mlx_font.c ./MLX42/src/mlx_cursor.c ./MLX42/src/mlx_exit.c ./MLX42/src/mlx_images.c ./MLX42/src/mlx_init.c ./MLX42/src/mlx_keys.c ./MLX42/src/mlx_loop.c ./MLX42/src/mlx_monitor.c ./MLX42/src/mlx_mouse.c ./MLX42/src/mlx_put_pixel.c ./MLX42/src/mlx_window.c ./MLX42/src/textures/mlx_png.c ./MLX42/src/textures/mlx_texture.c ./MLX42/src/textures/mlx_xpm42.c ./MLX42/src/utils/mlx_compare.c ./MLX42/src/utils/mlx_error.c ./MLX42/src/utils/mlx_list.c ./MLX42/src/utils/mlx_utils.c
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
	@$(COM) $(FLAGS) $(APPLE_FLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

.PHONY: all clean fclean re
