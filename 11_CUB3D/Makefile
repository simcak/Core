# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 17:00:26 by zdenek            #+#    #+#              #
#    Updated: 2024/12/18 11:26:34 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
COM				= cc
FLAGS			= -Wall -Wextra -Werror -g
APPLE_FLAGS		= -framework Cocoa -framework OpenGL -framework IOKit
LINUX_FLAGS		= -Iinc -Ilib/libft -ldl -lglfw -pthread -lm

MLX_DIR			= ./MLX42
MLX_LIB			= $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS		= -ldl -lglfw -pthread -lm -Ofast
COMPILER_SPEC	= -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

# Source directories and files
SRC_DIR			= ./algorithm/src
UTILS_DIR		= $(SRC_DIR)/0_utils
PARSER_DIR		= $(SRC_DIR)/2_parser
REYCAST_DIR		= $(SRC_DIR)/3_reycast
INIT_DIR		= $(SRC_DIR)/1_init

UTILS_SRC		= \
	0a_helpers.c \
	safe_free_zp.c \
	0b_helpers_zp.c \
	ft_gnl.c \
	ft_atoi.c \
	ft_strjoin.c \
	debug.c \
	ft_gnl_utils.c \
	ft_split.c \
	safe_malloc_zp.c \
	ft_substr.c \
	safe_exit.c \
	ft_str_utils.c

PARSER_SRC		= \
	4a_define_grid_zp.c \
	4_parser_map.c \
	3a_utils_zp.c \
	3_parser_color_zp.c \
	2_parser_texture_zp.c \
	4b_max_map_zp.c \
	1_parser_file_zp.c \
	2a_utils.c \
	0_parser_zp.c

REYCAST_SRC		= \
	3_key_down.c \
	2_put_mini_map.c \
	1a_wall_hit.c \
	1b_draw_ray.c \
	1_ray_cast.c

INIT_SRC		= \
	1_init_default.c \
	0_init_hub.c

MAIN_SRC		= ./algorithm/main_zp.c

# Combine all source files
SRC				= \
	$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
	$(addprefix $(PARSER_DIR)/, $(PARSER_SRC)) \
	$(addprefix $(REYCAST_DIR)/, $(REYCAST_SRC)) \
	$(addprefix $(INIT_DIR)/, $(INIT_SRC)) \
	$(MAIN_SRC)

OBJ				= $(SRC:%.c=%.o)
HEADER			= -I ./algorithm/includes/

# find ./algorithm -iname "*.c" -print0 | xargs -0 echo
# for dorker you have to:
# apt update
# apt install cmake
# apt install libgl1-mesa-dev xorg-dev
# apt install libglfw3 libglfw3-dev


RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

# Detect OS
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	OS_FLAGS = $(APPLE_FLAGS)
else
	OS_FLAGS = $(LINUX_FLAGS)
endif

all: mlx $(NAME)

%.o: %.c
	@$(COM) $(FLAGS) -c $< $(HEADER) -o $(<:.c=.o)

# MLX42
mlx:
	@if [ -d "$(MLX_DIR)" ]; then \
		cd $(MLX_DIR) && git pull; \
	else \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cd MLX42 && cmake -B build -D CMAKE_BUILD_TYPE=Release && cmake --build build -j4

$(NAME): $(OBJ)
	@$(COM) $(FLAGS) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) $(OS_FLAGS) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

# Cleans
clean_mlx:
	@rm -rf $(MLX_DIR)
	@printf "$(RED)----Deleted MLX42!----$(RST)\n"

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean clean_mlx
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

.PHONY: all mlx clean_mlx clean fclean re
