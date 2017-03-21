FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
FRAMEWORKS = -framework OpenGL -framework AppKit
MINILIB_X = minilibx_macos/libmlx.a

SRCS = \
		main.c \
		fdf_parsefile.c \
		translate_center.c

all:
	gcc $(FLAGS) $(SRCS) $(MINILIB_X) $(LIBFT) $(FRAMEWORKS) -o fdf