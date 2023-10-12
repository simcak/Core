# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 17:15:14 by lwoiton           #+#    #+#              #
#    Updated: 2023/08/16 12:43:33 by lwoiton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output files
PUSH_SWAP_NAME = push_swap
CHECKER_NAME = checker

# Directories
SRC_DIR = srcs
BONUS_DIR = bonus
OBJ_DIR = objs
BONUS_OBJ_DIR = $(OBJ_DIR)/$(BONUS_DIR)
INC_DIR = incl
LIB_DIR = libft

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INC_DIR) -I$(LIB_DIR)/incl

# Source files
COMMON_SRC_FILES = 00_linked_list.c \
                   00_rotate_operations.c \
                   00_stack_operations.c \
                   02a_parse_input.c \
                   02b_check_input.c \
                   utils_display_linked_list.c

PUSH_SWAP_SRC_FILES = $(COMMON_SRC_FILES) \
                      01_main.c \
                      03_analyse_ranks.c \
                      04_divide_into_chunks.c \
                      05_sort_five.c \
                      06a_calculate_rotations.c \
                      06b_read_ranks.c \
                      07_calculate_costs.c \
                      08_execute_sort.c

CHECKER_SRC_FILES = $(COMMON_SRC_FILES) \
                   $(BONUS_DIR)/checker_bonus.c

# Object files
PUSH_SWAP_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(PUSH_SWAP_SRC_FILES))
CHECKER_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(CHECKER_SRC_FILES))

# Header files
HEADER_FILES = $(wildcard $(INC_DIR)/*.h)

# Libraries
LIBFT = $(LIB_DIR)/libft.a

# Default targets
all: $(PUSH_SWAP_NAME)
bonus: $(CHECKER_NAME)

# Rule to build the push_swap executable
$(PUSH_SWAP_NAME): $(PUSH_SWAP_OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -g -o $@ $^

# Rule to build the checker executable
$(CHECKER_NAME): $(CHECKER_OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -g -o $@ $^

# Rule to build object files and include header dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -g -c -o $@ $<

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(HEADER_FILES) | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -g -c -o $@ $<

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $(BONUS_OBJ_DIR)

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

# Clean generated files
clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(PUSH_SWAP_NAME) $(CHECKER_NAME)

# Clean and build everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re libft
