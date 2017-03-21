#include "fdf.h"

int find_center_x(t_connection *obj)
{

	int x;
	float mean_x;
	x = 0;

	mean_x = obj->map.pts[x].local.x;
	while(x < obj->map.total_area)
		x++;
	x--;
	mean_x = mean_x + obj->map.pts[x].local.x;
	mean_x = mean_x / 2;
	return (mean_x);
}

int find_center_y(t_connection *obj)
{
	int x;
	float mean_y;

	x = 0;
	mean_y = obj->map.pts[x].local.y;
	while(x < obj->map.total_area)
		x++;
	x--;
	mean_y = mean_y + obj->map.pts[x].local.y;
	mean_y = mean_y / 2;

	return (mean_y);
}

int find_center_z(t_connection *obj)
{
	int x;
	float highest_z;
	float lowest_z;
	float mean_z;

	highest_z = 0;
	lowest_z = 0;

	x = 0;
	while(x < obj->map.total_area)
	{
		if (obj->map.pts[x].local.z > highest_z)
			highest_z = obj->map.pts[x].local.z;
		if (obj->map.pts[x].local.z < lowest_z)
			lowest_z = obj->map.pts[x].local.z;
		x++;
	}
	x--;
	mean_z = (highest_z + lowest_z) / 2;
	return (mean_z);
}

int translate_center(t_connection *obj, float mean_x, float mean_y, float mean_z)
{
	int x;

	x = 0;
	while(x < obj->map.total_area)
	{
		obj->map.pts[x].world.x = obj->map.pts[x].local.x - mean_x;
		obj->map.pts[x].world.y =  obj->map.pts[x].local.y - mean_y;
		obj->map.pts[x].world.z =  obj->map.pts[x].local.z - mean_z;
		x++;
	}
	return(0);
}

int translate_camera(t_connection *obj)
{
	int x;

	x = 0;
	while(x < obj->map.total_area)
	{
		obj->map.pts[x].camera.x = 	obj->map.pts[x].world.x + (SCREEN_WIDTH / 2);
		obj->map.pts[x].camera.y =  obj->map.pts[x].world.y + (SCREEN_HEIGHT / 2);
		obj->map.pts[x].camera.z =  obj->map.pts[x].world.z + -200;
		x++;
	}
	return(0);
}
