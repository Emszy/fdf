/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_n_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:25:04 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 15:25:06 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_win *obj)
{
	obj->map.zoom++;
	translate_center(obj, \
	find_center_x(obj), find_center_y(obj), find_center_z(obj));
}

void	zoom_out(t_win *obj)
{
	obj->map.zoom--;
	translate_center(obj, \
	find_center_x(obj), find_center_y(obj), find_center_z(obj));
}

void	rotate_x(t_win *obj, int cy, int cz, float radians)
{
	int x;

	x = 0;
	while (x < obj->map.total_area)
	{
		obj->map.rot.y = obj->map.pts[x].world.y - cy;
		obj->map.rot.z = obj->map.pts[x].world.z - cz;
		obj->map.rot.distance = hypot(obj->map.rot.y, obj->map.rot.z);
		obj->map.rot.theta = atan2(obj->map.rot.y, obj->map.rot.z) + \
		radians;
		obj->map.pts[x].world.z = cz + obj->map.rot.distance * \
		cos(obj->map.rot.theta);
		obj->map.pts[x].world.y = cy + obj->map.rot.distance * \
		sin(obj->map.rot.theta);
		x++;
	}
}

void	rotate_y(t_win *obj, int cx, int cz, float radians)
{
	int x;

	x = 0;
	while (x < obj->map.total_area)
	{
		obj->map.rot.x = obj->map.pts[x].world.x - cx;
		obj->map.rot.z = obj->map.pts[x].world.z - cz;
		obj->map.rot.distance = hypot(obj->map.rot.x, obj->map.rot.z);
		obj->map.rot.theta = atan2(obj->map.rot.x, obj->map.rot.z) + radians;
		obj->map.pts[x].world.z = cz + obj->map.rot.distance * \
		cos(obj->map.rot.theta);
		obj->map.pts[x].world.x = cx + obj->map.rot.distance * \
		sin(obj->map.rot.theta);
		x++;
	}
}

void	rotate_z(t_win *obj, int cx, int cy, float radians)
{
	int x;

	x = 0;
	while (x < obj->map.total_area)
	{
		obj->map.rot.x = obj->map.pts[x].world.x - cx;
		obj->map.rot.y = obj->map.pts[x].world.y - cy;
		obj->map.rot.distance = hypot(obj->map.rot.x, obj->map.rot.y);
		obj->map.rot.theta = atan2(obj->map.rot.x, obj->map.rot.y) + radians;
		obj->map.pts[x].world.y = cy + obj->map.rot.distance * \
		cos(obj->map.rot.theta);
		obj->map.pts[x].world.x = cx + obj->map.rot.distance * \
		sin(obj->map.rot.theta);
		x++;
	}
}
