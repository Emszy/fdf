/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_center.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:00:55 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 12:00:57 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		find_center_x(t_win *obj)
{
	int		x;
	float	mid_x;

	x = 0;
	mid_x = obj->map.pts[x].local.x;
	while (x < obj->map.total_area)
		x++;
	x--;
	mid_x = mid_x + obj->map.pts[x].local.x;
	mid_x = mid_x / 2;
	return (mid_x);
}

int		find_center_y(t_win *obj)
{
	int		x;
	float	mid_y;

	x = 0;
	mid_y = obj->map.pts[x].local.y;
	while (x < obj->map.total_area)
		x++;
	x--;
	mid_y = mid_y + obj->map.pts[x].local.y;
	mid_y = mid_y / 2;
	return (mid_y);
}

int		find_center_z(t_win *obj)
{
	int		x;
	float	highest_z;
	float	lowest_z;
	float	mid_z;

	highest_z = 0;
	lowest_z = 0;
	x = 0;
	while (x < obj->map.total_area)
	{
		if (obj->map.pts[x].local.z > highest_z)
			highest_z = obj->map.pts[x].local.z;
		if (obj->map.pts[x].local.z < lowest_z)
			lowest_z = obj->map.pts[x].local.z;
		x++;
	}
	x--;
	mid_z = (highest_z + lowest_z) / 2;
	return (mid_z);
}

int		translate_center(t_win *obj, float cx, float cy, float cz)
{
	int x;

	x = 0;
	while (x < obj->map.total_area)
	{
		obj->map.pts[x].world.x = (obj->map.pts[x].local.x - cx) \
			* obj->map.zoom;
		obj->map.pts[x].world.y = (obj->map.pts[x].local.y - cy) \
			* obj->map.zoom;
		obj->map.pts[x].world.z = (obj->map.pts[x].local.z - cz) \
			* obj->map.zoom;
		x++;
	}
	return (0);
}

int		translate_camera(t_win *obj)
{
	int x;

	x = 0;
	while (x < obj->map.total_area)
	{
		obj->map.pts[x].camera.x = obj->map.pts[x].world.x \
			+ (SCREEN_WIDTH / 2);
		obj->map.pts[x].camera.y = obj->map.pts[x].world.y \
			+ (SCREEN_HEIGHT / 2);
		obj->map.pts[x].camera.z = obj->map.pts[x].world.z + -666;
		x++;
	}
	return (0);
}
