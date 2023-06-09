# _*_ MakeFile _*_

CC = gcc
CFLAGS = -Wextra -Wall -Werror -fsanitize=address 
# -D HEIGHT=1000 -D WIDTH=1000 -D ZOOM=10

NAME = miniRT
MLX = libmlx.a
LIBFT = libft.a

SRCS = src/main.c \
		src/events.c \
		src/sphere.c \
		src/vec3.c \
		src/color.c \
		src/vec3_utils.c \
		src/light.c \
		src/image.c \
		src/utils.c \
		src/cylinder.c \
		src/cylinder_utils.c \
		src/obj.c \
		src/move.c \
		src/zoom.c \
		src/mat3.c \
		src/plane.c \
		src/shadow.c \
		src/parse.c \
		src/parse_utils.c \
		src/parse_objects.c \
		src/parse_elements.c \
		src/error.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	$(MAKE) -C mlx
	cp mlx/$(MLX) $(MLX)

$(LIBFT):
	$(MAKE) -C libft
	mv libft/$(LIBFT) $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx
	rm -f $(OBJS) 
	rm -rf *.dSYM

fclean: clean
	rm -f $(NAME) $(MLX) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
