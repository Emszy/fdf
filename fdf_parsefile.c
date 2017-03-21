#include "fdf.h"

int add_pts(char **split_line, int line_count, t_connection *obj, int index)
{
	int x;
	x = 0;

	while (split_line[x] != '\0')
	{
		obj->map.pts[index].local.x = x;
		obj->map.pts[index].local.y = line_count;
		obj->map.pts[index].local.z = ft_atoi(split_line[x]) * 3;
		index++;
		x++;
	}

	return (index);
}


int check_valid_file(char *filename, t_connection *obj)
{
	int x;
	int fd;
	int line_count;
	char *line;
	char **split_line;

	line_count = 0;
	x = 0;
	fd = open(filename, O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		x = 0;
		while(split_line[x])
			x++;
		obj->map.map_width = x;
		line_count++;
	}
	obj->map.map_height = line_count;

	return (1);
}

void print_map(t_connection *obj)
{
	int x;

	x = 0;
	while(x < obj->map.total_area)
	{
		printf("x:%f\n", obj->map.pts[x].local.x);
		printf("y:%f\n", obj->map.pts[x].local.y);
		printf("z:%f\n", obj->map.pts[x].local.z);
		x++;
	}
}

int read_file(char *filename, t_connection *obj)
{
	int fd;
	int line_count;
	char *line;
	char **split_line;
	int x;
	int index;

	index = 0;
	x = 0;
	line_count = 0;

	check_valid_file(filename, obj);
	obj->map.total_area = obj->map.map_height * obj->map.map_width;
	obj->map.pts = (t_store*)malloc(sizeof(t_store) * obj->map.total_area);
	

	fd = open(filename, O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		index = add_pts(split_line, line_count, obj, index);
		line_count++;
	}

	x = 0;
	return (1);

}
