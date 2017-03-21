/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:54:14 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 11:54:17 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_tmp_variables(t_win *obj)
{
	obj->map.tmp_ln.x = obj->map.tmp_ln.x1;
	obj->map.tmp_ln.y = obj->map.tmp_ln.y1;
	obj->map.tmp_ln.dx = abs(obj->map.tmp_ln.x2 - obj->map.tmp_ln.x1);
	obj->map.tmp_ln.dy = abs(obj->map.tmp_ln.y2 - obj->map.tmp_ln.y1);
	obj->map.tmp_ln.s1 = sign(obj->map.tmp_ln.x2 - obj->map.tmp_ln.x1);
	obj->map.tmp_ln.s2 = sign(obj->map.tmp_ln.y2 - obj->map.tmp_ln.y1);
	obj->map.tmp_ln.swap = 0;
	if (obj->map.tmp_ln.dy > obj->map.tmp_ln.dx)
	{
		obj->map.tmp_ln.temp = obj->map.tmp_ln.dx;
		obj->map.tmp_ln.dx = obj->map.tmp_ln.dy;
		obj->map.tmp_ln.dy = obj->map.tmp_ln.temp;
		obj->map.tmp_ln.swap = 1;
	}
}

void	draw_line(t_win *obj)
{
	int i;

	i = -1;
	init_tmp_variables(obj);
	mlx_pixel_put(obj->mlx, obj->win, obj->map.tmp_ln.x, obj->map.tmp_ln.y, G);
	obj->map.tmp_ln.p = 2 * obj->map.tmp_ln.dy - obj->map.tmp_ln.dx;
	while (++i < obj->map.tmp_ln.dx)
	{
		mlx_pixel_put(obj->mlx, obj->win, \
		obj->map.tmp_ln.x, obj->map.tmp_ln.y, G);
		while (obj->map.tmp_ln.p >= 0)
		{
			obj->map.tmp_ln.p = obj->map.tmp_ln.p - 2 * obj->map.tmp_ln.dx;
			if (obj->map.tmp_ln.swap)
				obj->map.tmp_ln.x += obj->map.tmp_ln.s1;
			else
				obj->map.tmp_ln.y += obj->map.tmp_ln.s2;
		}
		obj->map.tmp_ln.p = obj->map.tmp_ln.p + 2 * obj->map.tmp_ln.dy;
		if (obj->map.tmp_ln.swap)
			obj->map.tmp_ln.y += obj->map.tmp_ln.s2;
		else
			obj->map.tmp_ln.x += obj->map.tmp_ln.s1;
	}
	mlx_pixel_put(obj->mlx, obj->win, obj->map.tmp_ln.x, obj->map.tmp_ln.y, G);
}

void	connect_x_pts(t_win *obj)
{
	int x;
	int y;
	int count;

	count = 0;
	x = -1;
	y = -1;
	while (++y <= obj->map.map_height)
	{
		while (x < obj->map.map_width * count - 1)
		{
			obj->map.tmp_ln.x1 = obj->map.pts[x].camera.x;
			obj->map.tmp_ln.y1 = obj->map.pts[x].camera.y;
			obj->map.tmp_ln.x2 = obj->map.pts[x + 1].camera.x;
			obj->map.tmp_ln.y2 = obj->map.pts[x + 1].camera.y;
			draw_line(obj);
			x++;
		}
		x++;
		count++;
	}
}

void	connect_y_pts(t_win *obj)
{
	int x;
	int y;
	int c;
	int count;

	c = 0;
	count = 0;
	x = -2;
	y = 0;
	while (++x < obj->map.map_width)
	{
		while (y < obj->map.map_height * count)
		{
			obj->map.tmp_ln.x1 = obj->map.pts[c].camera.x;
			obj->map.tmp_ln.y1 = obj->map.pts[c].camera.y;
			obj->map.tmp_ln.x2 = obj->map.pts[c + obj->map.map_width].camera.x;
			obj->map.tmp_ln.y2 = obj->map.pts[c + obj->map.map_width].camera.y;
			draw_line(obj);
			y++;
			c++;
		}
		y++;
		count++;
	}
}
