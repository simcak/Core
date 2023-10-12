# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 18:52:19 by lwoiton           #+#    #+#              #
#    Updated: 2023/08/15 16:09:21 by lwoiton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output file
NAME = libft.a

# Directories
SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = incl

# Source files
SRC_FILES = ft_putstr_fd.c \
            ft_putendl_fd.c \
            ft_atoi.c \
            ft_strtrim.c \
            ft_itoa.c \
            ft_strnstr.c \
            ft_printf/ft_printf.c \
            ft_printf/conversion_utils.c \
            ft_printf/print.c \
            ft_printf/print_int.c \
            ft_printf/print_utils.c \
            ft_memmove.c \
            ft_putnbr_fd.c \
            ft_memchr.c \
            ft_strrchr.c \
            ft_strchr.c \
            ft_strdup.c \
            ft_memcmp.c \
            get_next_line/get_next_line_utils.c \
            get_next_line/get_next_line.c \
            ft_substr.c \
            ft_tolower.c \
            ft_isalnum.c \
            ft_strlen.c \
            ft_isdigit.c \
            ft_calloc.c \
            ft_strjoin.c \
            ft_isprint.c \
            ft_strmapi.c \
            ft_split.c \
            ft_toupper.c \
            ft_strlcat.c \
            ft_bzero.c \
            ft_isalpha.c \
            ft_memset.c \
            ft_striteri.c \
            ft_isascii.c \
            ft_strlcpy.c \
            ft_memcpy.c \
            ft_putchar_fd.c \
            ft_strncmp.c 
#            ft_lstdelone.c \
#            ft_lstsize.c \
#            ft_lstlast.c \
#            ft_lstclear.c \
#            ft_lstmap.c \
#            ft_lstnew.c \
#            ft_lstiter.c \
#            ft_lstadd_front.c \
#            ft_lstadd_back.c

# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INC_DIR)

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Rule to build the archive file
$(NAME): $(OBJ_FILES)
	ar rcs $@ $^

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $@/ft_printf
	mkdir -p $@/get_next_line

# Clean generated files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and build everything
re: fclean all
