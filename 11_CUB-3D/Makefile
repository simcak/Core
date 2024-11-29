# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 13:49:49 by psimcak           #+#    #+#              #
#    Updated: 2024/11/29 12:39:35 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
COM				= cc
FLAGS			= -Wall -Wextra -Werror -g
APPLE_FLAGS		= -framework Cocoa -framework OpenGL -framework IOKit

MLX_DIR			= ./MLX42
MLX_LIB			= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm -Ofast
COMPILER_SPEC	= -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

SRC				= $(shell find ./algorithm -iname "*.c")
OBJ				= $(SRC:%.c=%.o)
HEADER			= -I ./algorithm/inc/

# find ./algorithm -iname "*.c" -print0 | xargs -0 echo

RED		= \033[31m
GREEN	= \033[32m
RST		= \033[0m

all: lib_m $(NAME)

%.o: %.c
	@$(COM) $(FLAGS) -c $< $(HEADER) -o $(<:.c=.o)

lib_m:
	@if [ ! -f $(MLX_DIR)/build/libmlx42.a ]; then \
		cmake $(MLX_DIR) $(COMPILER_SPEC) -B $(MLX_DIR)/build; \
		make -C $(MLX_DIR)/build -j4; \
		printf "$(GREEN)----MLX42 library ready!----$(RST)\n"; \
	else \
		printf "$(GREEN)----MLX42 library already built!----$(RST)\n"; \
	fi

$(NAME): $(OBJ)
	@$(COM) $(FLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)
	@printf "$(GREEN)----$(NAME) Compiled!----$(RST)\n"

clean:
	@rm -f $(OBJ)
	@printf "$(RED)----Deleting o-files!----$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@printf "$(RED)----Deleting o-files & $(NAME) file----$(RST)\n"

re: fclean all

.PHONY: all clean fclean re
