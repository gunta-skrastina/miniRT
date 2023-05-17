# _*_ MakeFile _*_

CC = gcc
CFLAGS = -Wextra -Wall -Werror -fsanitize=address

NAME = miniRT
LIBFT = libft.a
MLX = libmlx.a

SRCS = main.c events.c sphere.c parse.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C mlx
	cp mlx/$(MLX) $(MLX)

$(LIBFT):
	$(MAKE) -C libft
	cp libft/$(LIBFT) $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJS) 
	rm -rf *.dSYM
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(MLX) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
