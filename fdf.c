/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:37:33 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 15:37:35 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		my_funct(int keycode, t_win *obj)
{
	if (keycode == 53)
		error_master5000("GOODBYE WORLD!");
	mlx_clear_window(obj->mlx, obj->win);
	if (keycode == 1)
		rotate_x(obj, find_center_y(obj), find_center_z(obj), 0.1);
	if (keycode == 13)
		rotate_x(obj, find_center_y(obj), find_center_z(obj), -0.1);
	if (keycode == 2)
		rotate_y(obj, find_center_x(obj), find_center_z(obj), 0.1);
	if (keycode == 0)
		rotate_y(obj, find_center_x(obj), find_center_z(obj), -0.1);
	if (keycode == 6)
		zoom_in(obj);
	if (keycode == 7)
		zoom_out(obj);
	if (keycode == 12)
		rotate_z(obj, find_center_x(obj), find_center_y(obj), 0.1);
	if (keycode == 14)
		rotate_z(obj, find_center_x(obj), find_center_y(obj), -0.1);
	translate_camera(obj);
	connect_x_pts(obj);
	connect_y_pts(obj);
	return (0);
}

int		main(int ac, char **av)
{
	t_win	*obj;
	int		fd;

	fd = 0;
	obj = malloc(sizeof(t_win));
	obj->mlx = mlx_init();
	obj->win = mlx_new_window(obj->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "MZ$2");
	if (ac == 2)
	{
		read_file(av[1], obj, fd);
		first_display(obj);
		mlx_key_hook(obj->win, my_funct, obj);
		mlx_loop(obj->mlx);
	}
	else
		error_master5000("-Invalid-\n Usage: \n ./fdf filename");
	return (0);
}
