NAME = fractol
CFLAGS := -Wall -Wextra -Werror
LIBMLX := ./minilibx-linux
CC = cc
HEADERS := fractol.h -I $(LIBMLX)/mlx.h
LIBS := $(LIBMLX)/libmlx.a -Imlx_linux -lXext -lX11
SRCS := main.c init.c events.c render.c utils1.c utils2.c
OBJS := ${SRCS:.c=.o}

minilibx:
	cd ./minilibx-linux && make

all: minilibx $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $@ $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
