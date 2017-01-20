#include "fdf.h"

void add_to_2darr(char **split_line, t_coordinate *coordinate, t_map *map, int y_count)
{
	int i;
	 
	i = -1;
	coordinate->points[y_count] = malloc(sizeof(int *) * (map->col_count));
	while(++i < map->col_count)
	{
		coordinate->points[y_count][i] = ft_atoi(split_line[i]);
		if (coordinate->points[y_count][i] > coordinate->z_len)
			coordinate->z_len = coordinate->points[y_count][i];
	}
}

int read_file(char **av, t_map *map, t_coordinate *coordinate)
{	char *line;
	char **split_line;
	int fd;
	int x;
	int y;

	x = 0;
	y = 0;
	fd = open(av[1], O_RDONLY);
	coordinate->points = (int **)malloc(sizeof(int **) * map->row_count + 2);
	while(get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		add_to_2darr(split_line, coordinate, map, y);
		y++;
	}

	return (1);
}
int count_x(char **split_line)
{
	int x;

	x = 0;
	while(split_line[x])
		x++;
	return (x);
}

int get_file_length(char **av, t_map *map)
{
	int fd;
	char *line;
	char **split_line;
	int y_count;
	int x_count;

	y_count = 0;
	x_count = 0;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		if (!x_count)
			x_count = count_x(split_line);
		if (count_x(split_line) != x_count)
			error_master5000("ITS NOT A RECTANGLE BRO!");
		y_count++;
	}
	map->row_count = y_count;
	map->col_count = x_count;
	map->area = y_count * x_count;
	close(fd);
	return(1);
}