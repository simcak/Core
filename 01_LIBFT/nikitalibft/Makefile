# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nandroso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 15:12:45 by nandroso          #+#    #+#              #
#    Updated: 2023/08/22 15:46:14 by nandroso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
AR = ar	# The archiver tool used to create static libraries
CC = cc
RM = rm
COMPILER_FLAGS = -Wall -Wextra -Werror

SRC = 	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\

BON =	ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c

OBJ = $(SRC:%.c=%.o)
OBJ_BON = $(BON:%.c=%.o)
# OBJ is var for names of the object files only

# Object File Compilation
%.o: %.c	# %.o = target = $@ AND %.c = prerequisite = $<
	$(CC) $(COMPILER_FLAGS) -c $< -o $@
# The OBJ variable tells 'make' what .o files are needed,\
and the Object File Compilation rule tells 'make' how to create them.
# c = This flag tells the compiler to generate an .o file (compile not link)
# o = This flag specifies the output file name

all: $(OBJ)
	$(AR) -rcs $(NAME) $(OBJ)
# r = Replace or insert .o files into archive (if it doesn't exist, create it)
# c = Don't warn if the archive had to be created
# s = Create an archive index (time saving)

bonus: $(OBJ) $(OBJ_BON)
	$(AR) -rcs $(NAME) $(OBJ) $(OBJ_BON)

clean:
	$(RM) -f $(OBJ) $(OBJ_BON)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
# if there is a file called all clean etc. - it will not mess up the code