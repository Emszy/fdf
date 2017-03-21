/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsefile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:30:19 by ebucheit          #+#    #+#             */
/*   Updated: 2017/03/21 11:30:21 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		add_pts(char **split_line, int line_c, t_win *obj, int i)
{
	int x;

	x = 0;
	while (split_line[x] != '\0')
	{
		obj->map.pts[i].local.x = x;
		obj->map.pts[i].local.y = line_c;
		obj->map.pts[i].local.z = ft_atoi(split_line[x]);
		i++;
		x++;
	}
	return (i);
}

int		check_if_square(t_win *obj, int x, int line_count)
{
	if (obj->map.map_width == 0)
		obj->map.map_width = x;
	if (obj->map.map_width != x || obj->map.map_width == 0)
		error_master5000("Not a Rectangle");
	line_count++;
	return (line_count);
}

int		check_valid_file(char *filename, t_win *obj)
{
	int		x;
	int		fd;
	int		line_count;
	char	*line;
	char	**split_line;

	line_count = 0;
	x = 0;
	obj->map.map_width = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		x = 0;
		while (split_line[x])
			x++;
		line_count = check_if_square(obj, x, line_count);
	}
	obj->map.map_height = line_count;
	if (obj->map.map_width < 1 || obj->map.map_height < 1)
		error_master5000("BLANK");
	return (1);
}

int		read_file(char *filename, t_win *obj, int fd)
{
	int		line_count;
	char	*line;
	char	**split_line;
	int		x;
	int		index;

	index = 0;
	x = 0;
	line_count = 0;
	check_valid_file(filename, obj);
	obj->map.total_area = obj->map.map_height * obj->map.map_width;
	if ((obj->map.pts = (t_store*)malloc(sizeof(t_store) * \
		obj->map.total_area)) == NULL)
		error_master5000("NOMEM");
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		index = add_pts(split_line, line_count, obj, index);
		line_count++;
	}
	return (1);
}
