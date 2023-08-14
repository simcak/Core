# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 11:40:46 by psimcak           #+#    #+#              #
#    Updated: 2023/08/14 16:36:09 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = LIBFT.h
AR = ar	# The archiver tool used to create static libraries
CC = cc
RM = rm
COMPILER_FLAGS = -Wall -Wextra -Werror

SRC = 	ft_atoi.c\
		ft_strlen.c

OBJ = $(SRC:%.c=%.o)
# OBJ is var for names of the object files only

all: $(NAME)

$(NAME) : $(OBJ)
	$(AR) -rcs $@ $(OBJ)
# r = Replace or insert .o files into archive (if it doesn't exist, create it)
# c = Don't warn if the archive had to be created
# s = Create an archive index (time saving)

# Object File Compilation
%.o: %.c	# %.o = target = $@ AND %.c = prerequisite = $<
	$(CC) $(COMPILER_FLAGS) -c $< -o $@
# The OBJ variable tells 'make' what .o files are needed,\
and the Object File Compilation rule tells 'make' how to create them.
# c = This flag tells the compiler to generate an .o file (compile not link)
# o = This flag specifies the output file name

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
# if there is a file called all clean etc. - it will not mess up the code
