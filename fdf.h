/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:23:43 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 11:23:46 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define SCREEN_WIDTH 	1280
# define SCREEN_HEIGHT 	1000
# define X_SCALE 		100
# define Y_SCALE 		100
# define RED 			0x00FF0000
# define GREEN 			0x0000FF00
# define G				0x0000FA00
# define BLUE 			0x000000FF

typedef struct	s_pts
{
	float x;
	float y;
	float z;
}				t_pts;

typedef struct	s_store
{
	t_pts		local;
	t_pts		world;
	t_pts		camera;
	t_pts		view;
}				t_store;

typedef struct	s_rotation
{
	float x;
	float y;
	float z;
	float theta;
	float distance;
}				t_rotation;

typedef struct	s_tmp_ln
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
}				t_tmp_ln;

typedef struct	s_map
{
	int			map_width;
	int			map_height;
	int			total_area;
	int			zoom;
	t_store		*pts;
	t_tmp_ln	tmp_ln;
	t_rotation	rot;
}				t_map;

typedef struct	s_connection
{
	void			*mlx;
	void			*win;
	void			*img;
	t_map			map;
}				t_win;

void			error_master5000(char *message);
int				add_pts(char **split_line, int line_c, t_win *obj, int i);
int				check_valid_file(char *filename, t_win *obj);
int				read_file(char *filename, t_win *obj, int fd);
int				find_center_x(t_win *obj);
int				find_center_y(t_win *obj);
int				find_center_z(t_win *obj);
int				translate_center(t_win *obj, float cx, float cy, float cz);
int				translate_camera(t_win *obj);
void			zoom_in(t_win *obj);
void			zoom_out(t_win *obj);
void			rotate_x(t_win *obj, int cy, int cz, float radians);
void			rotate_y(t_win *obj, int cx, int cz, float radians);
void			rotate_z(t_win *obj, int cx, int cy, float radians);
void			draw_line(t_win *obj);
void			connect_x_pts(t_win *obj);
void			connect_y_pts(t_win *obj);
void			init_tmp_lniables(t_win *obj);
int				sign(int x);
void			error_master5000(char *message);
void			translate_points(t_win *obj, int dir_x, int dir_y);
void			first_display(t_win *obj);

#endif
