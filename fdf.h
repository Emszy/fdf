#ifndef _FDF_
# define _FDF_

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1000
#define X_SCALE 30
#define Y_SCALE 30

#define RED 	0x00FF0000
#define GREEN 	0x0000FF00
#define BLUE 	0x000000FF

typedef struct s_coordinate
{
	int **points;
	int temp_x;
	int temp_y;
	int temp_z;
	int z_len;
	struct s_coordinate *next;
}				t_coordinate;

typedef struct s_map
{
	int row_count;
	int col_count;
	int z_len;
	int area;
	int start_point_x;
	int start_point_y;
	int x_sum;
	int y_sum;

}				t_map;
typedef struct	s_connection
{
	void *mlx;
	void *win;
	void *img;
}				t_connection;

typedef struct	s_move_grid
{

	double zoom;
	double transform_x;
	double transform_y;
	double slope;
	double x_radians;
	double y_radians;
	double z_radians;
	double radian_z;
	double fov;

}				t_move_grid;

typedef struct s_all
{
	t_coordinate *coordinate;
	t_map *map;
	t_connection *connection;
	t_move_grid *move_grid;
}				t_all;

void error_master5000(char *message);
int my_funct(int keycode, t_all *all);
void print_coordinates(t_all *all);
void add_to_2darr(char **split_line, t_coordinate *coordinate, t_map *map, int y_count);
int read_file(char **av, t_map *map, t_coordinate *coordinate);
int count_x(char **split_line);
int get_file_length(char **av, t_map *map);
void mlx_connections(t_all *all);
void malloc_a_skeleton(t_all *all);

#endif


