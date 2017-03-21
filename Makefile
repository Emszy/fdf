FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
FRAMEWORKS = -framework OpenGL -framework AppKit
MINILIB_X = minilibx_macos/libmlx.a

SRCS = \
		fdf.c \
		fdf_parsefile.c \
		translate_center.c \
		zoom_n_rot.c \
		lines.c \
		misc.c

all:
	gcc $(FLAGS) $(SRCS) $(MINILIB_X) $(LIBFT) $(FRAMEWORKS) -o fdf