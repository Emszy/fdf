#include "fdf.h"

int sign(x)
{
	if (x > 0)
		return(1);
	if (x < 0)
		return(-1);
	else
		return(0);
}

void error_master5000(char *message)
{
	ft_putstr(message);
	ft_putstr("\n");
	exit(-1);
}

void translate_points(t_win *obj, int dir_x, int dir_y)
{
	int x;

	x = 0;
	while(x < obj->map.total_area)
	{
		obj->map.pts[x].camera.y = (((SCREEN_HEIGHT / 2) - obj->map.pts[x].camera.y) + dir_y) + (SCREEN_HEIGHT / 2);
		obj->map.pts[x].camera.x = (((SCREEN_WIDTH / 2) - obj->map.pts[x].camera.x) + dir_x) + (SCREEN_WIDTH / 2);
		x++;
	}
}

void first_display(t_win *obj)
{
	translate_center(obj ,find_center_x(obj), find_center_y(obj), find_center_z(obj));
	zoom_in(obj);
	translate_camera(obj);
	connect_x_pts(obj);
	connect_y_pts(obj);
}
