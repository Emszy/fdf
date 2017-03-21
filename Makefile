NAME = fdf
MINILIB_X = minilibx_macos/libmlx.a

FLAGS = -Wall -Wextra -Werror

SRC =	\
		fdf.c \
		fdf_parsefile.c \
		translate_center.c \
		zoom_n_rot.c \
		lines.c \
		misc.c


OBJ = $(patsubst %.c,%.o,$(addprefix ./, $(SRC)))


all: $(NAME)

$(NAME): $(OBJ) fdf.h
	make -C libft/
	gcc $(FLAGS) -I /libft -c $(SRC)
	gcc -o $(NAME) $(OBJ) -lm -L libft/ -lft $(MINILIB_X) -framework OpenGL -framework AppKit

.PHONY: clean fclean

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all