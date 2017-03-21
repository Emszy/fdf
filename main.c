#include "fdf.h"

void error_master5000(char *message)
{
	ft_putstr(message);
	ft_putstr("\n");
	exit(-1);
}

void display_map(t_connection *obj)
{
	int x;

	x = 0;
	while(x < obj->map.total_area)
	{
		mlx_pixel_put(obj->mlx, obj->win, obj->map.pts[x].camera.x, obj->map.pts[x].camera.y, GREEN);
		x++;
	}
}

void translate_points(t_connection *obj, int dir_x, int dir_y)
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

void zoom_in(t_connection *obj)
{
	
	obj->map.zoom++;
	translate_center(obj ,find_center_x(obj), find_center_y(obj), find_center_z(obj));
}

void zoom_out(t_connection *obj)
{
	
		obj->map.zoom--;
		translate_center(obj ,find_center_x(obj), find_center_y(obj), find_center_z(obj));
}

void rotate_x(t_connection *obj, int cy, int cz, float radians)
 {
 	int x;

 	x = 0;
 
 	while(x < obj->map.total_area)
	{
		obj->map.rot.y     			= obj->map.pts[x].world.y - cy;
        obj->map.rot.z      		= obj->map.pts[x].world.z - cz;
        obj->map.rot.distance      	= hypot(obj->map.rot.y, obj->map.rot.z);
        obj->map.rot.theta  		= atan2(obj->map.rot.y, obj->map.rot.z) + radians;
        obj->map.pts[x].world.z 	= cz + obj->map.rot.distance * cos(obj->map.rot.theta);
       	obj->map.pts[x].world.y 	= cy + obj->map.rot.distance * sin(obj->map.rot.theta);
		x++;
	}  
 }



 void rotate_y(t_connection *obj, int cx, int cz, float radians)
 {
 	int x;

 	x = 0;
 
 	while(x < obj->map.total_area)
	{
		obj->map.rot.x     	= obj->map.pts[x].world.x - cx;
        obj->map.rot.z      = obj->map.pts[x].world.z - cz;
        obj->map.rot.distance      = hypot(obj->map.rot.x, obj->map.rot.z);
        obj->map.rot.theta  = atan2(obj->map.rot.x, obj->map.rot.z) + radians;
        obj->map.pts[x].world.z = cz + obj->map.rot.distance * cos(obj->map.rot.theta);
       	obj->map.pts[x].world.x = cx + obj->map.rot.distance * sin(obj->map.rot.theta);

		x++;
	}
 }

void rotate_z(t_connection *obj, int cx, int cy, float radians)
 {
 	int x;

 	x = 0;

 	while(x < obj->map.total_area)
	{
		obj->map.rot.x     	= obj->map.pts[x].world.x - cx;
        obj->map.rot.y      = obj->map.pts[x].world.y - cy;
        obj->map.rot.distance      = hypot(obj->map.rot.x, obj->map.rot.y);
        obj->map.rot.theta  = atan2(obj->map.rot.x, obj->map.rot.y) + radians;
        obj->map.pts[x].world.y = cy + obj->map.rot.distance * cos(obj->map.rot.theta);
       	obj->map.pts[x].world.x = cx + obj->map.rot.distance * sin(obj->map.rot.theta);

		x++;
	}
 }

#define sign(x) ((x>0)?1:((x<0)?-1:0))

void draw_line(int x1, int y1, int x2, int y2, t_connection *obj)
{

	int x;
	int y;
	int dx;
	int dy;
	int swap;
	int temp;
	int s1;
	int s2;
	int p;
	int i;

	x = x1;
	y = y1;
	dx = abs(x2-x1);
	dy = abs(y2-y1);
	s1 = sign(x2-x1);
	s2 = sign(y2-y1);
	swap = 0;
	i = -1;


	mlx_pixel_put(obj->mlx, obj->win, x, y, GREEN);
	if(dy>dx)
 	{
 		temp=dx;
 		dx=dy;
 		dy=temp;
 		swap=1;
 	}
	p=2*dy-dx;

	while(++i < dx)
 	{
 		mlx_pixel_put(obj->mlx, obj->win, x, y, GREEN);
 		while(p>=0)
  		{
  			p=p-2*dx;
  			if(swap)
   				x+=s1;
  			else
   				y+=s2;
  		}
 	p = p + 2 * dy;
 	if (swap)
  		y+=s2;
 	else
  		x+=s1;
 }
	mlx_pixel_put(obj->mlx, obj->win, x, y, GREEN);
}





void connect_x_pts(t_connection *obj)
{
	int x;
	int y;
	int count;

	count = 0;
 	x = -1;
 	y = 0;

while(y <= obj->map.map_height)
{
	while(x < obj->map.map_width * count - 1)
	{
			draw_line(obj->map.pts[x].camera.x, obj->map.pts[x].camera.y, obj->map.pts[x + 1].camera.x, obj->map.pts[x + 1].camera.y, obj);
		x++;
	}
	x++;
	y++;
	count++;
}
}

void connect_y_pts(t_connection *obj)
{
	int x;
	int y;
	int c;
	int count;
	c = 0;
	count = 0;
 	x = -1;
 	y = 0;

	while(x < obj->map.map_width)
	{
		while(y < obj->map.map_height * count)
		{
				draw_line(obj->map.pts[c].camera.x, obj->map.pts[c].camera.y, obj->map.pts[c + obj->map.map_width].camera.x, obj->map.pts[c + obj->map.map_width].camera.y, obj);
			y++;
			c++;
		}
	x++;
	y++;
	count++;
	}
}
void setup_line(t_connection *obj)
{
	connect_x_pts(obj);
	connect_y_pts(obj);
}

int my_funct(int keycode, t_connection *obj)
{
	
	if (keycode == 53)
		error_master5000("GOODBYE WORLD!");
		if (keycode == 1)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		  rotate_x(obj, find_center_y(obj), find_center_z(obj), 0.1);
		  translate_camera(obj);
		  display_map(obj);
		}
		if (keycode == 13)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		  rotate_x(obj, find_center_y(obj), find_center_z(obj), -0.1);
		  translate_camera(obj);
		  display_map(obj);
		
		}
		if (keycode == 2)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		  rotate_y(obj, find_center_x(obj), find_center_z(obj), 0.1);
		  translate_camera(obj);
		  display_map(obj);
		}

		if (keycode == 0)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		  rotate_y(obj, find_center_x(obj), find_center_z(obj), -0.1);
		  translate_camera(obj);
		  display_map(obj);
		
		}
		if (keycode == 6)
		{
				mlx_clear_window(obj->mlx, obj->win);
		 		zoom_in(obj);
		 	 	translate_camera(obj);
		 	 	display_map(obj);
		}
		if (keycode == 7)
		{
				mlx_clear_window(obj->mlx, obj->win);
		 		zoom_out(obj);
		 	 	translate_camera(obj);
		 	 	display_map(obj);
		}
		if (keycode == 12)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		  rotate_z(obj, find_center_x(obj), find_center_y(obj), 0.1);
		  translate_camera(obj);
		  display_map(obj);
		 
		}
		if (keycode == 14)
		{
		  	mlx_clear_window(obj->mlx, obj->win);
		  rotate_z(obj, find_center_x(obj), find_center_y(obj), -0.1);
		  translate_camera(obj);
		  display_map(obj);
		}
		if (keycode == 5)
		{
		  mlx_clear_window(obj->mlx, obj->win);
		}
	setup_line(obj);
	printf("%d\n", keycode);
	return(0);
}

int main(int ac, char **av)
{
	t_connection *obj;
	obj = malloc(sizeof(t_connection));
	obj->mlx = mlx_init();
	obj->win = mlx_new_window(obj->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "MZ$2");
	if (ac == 2)
	{
		read_file(av[1], obj);
		translate_center(obj ,find_center_x(obj), find_center_y(obj), find_center_z(obj));
		zoom_in(obj);
		translate_camera(obj);
		setup_line(obj);
	}
	mlx_key_hook(obj->win, my_funct, obj);
	mlx_loop(obj->mlx);

	
	return 0;
}
