# _*_ MakeFile _*_

CC = gcc
CFLAGS = -Wextra -Wall -Werror -fsanitize=address

NAME = miniRT
MLX = libmlx.a

SRCS = main.c events.c sphere.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C mlx
	cp mlx/$(MLX) $(MLX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJS) 
	rm -rf *.dSYM

fclean: clean
	rm -f $(NAME) $(MLX)

re: fclean all

.PHONY: all clean fclean re
