CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rc
RM = rm -f


SRC = $(shell find ./ -iname "*.c")
OBJ = $(SRC:%.c=%.o)
LIB = libftprintf.a
NAME = libftprintf.a
HEADER = ft_printf.h

all: $(NAME)

$(NAME) : $(OBJ)
	$(AR) -rcs $(@) $(OBJ)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I$(HEADER) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re