#ifndef _FDF_
# define _FDF_

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1000
#define X_SCALE 100
#define Y_SCALE 100

#define RED 	0x00FF0000
#define GREEN 	0x0000FF00
#define BLUE 	0x000000FF



typedef struct s_pts
{
	float x;
	float y;
	float z;
}				t_pts;

typedef struct s_store
{
	t_pts		local;
	t_pts		world;
	t_pts		camera;
	t_pts		view;
}				t_store;

typedef struct s_rotation
{
	float x;
	float y;
	float z;
	float theta;
	float distance;
}				t_rotation;

typedef struct	s_line_var
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x;
	int y;
	int dx;
	int dy;
	int swap;
	int temp;
	int s1;
	int s2;
	int p;
	
}				t_line_var;

typedef struct s_map
{
	int 				map_width;
	int 				map_height;
	int 				total_area;
	int					zoom;

	t_store				*pts;
	t_line_var			line_var;
	t_rotation			rot;
}				t_map;



typedef struct	s_connection
{
	void			*mlx;
	void			*win;
	void			*img;
	t_map			map;
}				t_connection;



int add_pts(char **split_line, int line_count, t_connection *obj, int index);
int check_valid_file(char *filename, t_connection *obj);
void print_map(t_connection *obj);
int read_file(char *filename, t_connection *obj);
int find_center_x(t_connection *obj);
int find_center_y(t_connection *obj);
int find_center_z(t_connection *obj);
int translate_center(t_connection *obj, float mean_x, float mean_y, float mean_z);
int translate_camera(t_connection *obj);




#endif


