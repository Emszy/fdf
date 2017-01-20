#include "fdf.h"

void error_master5000(char *message)
{
	ft_putstr(message);
	ft_putstr("\n");
	exit(-1);
}

void print_coordinates(t_all *all)
{
	int x;
	int y;

	x = -1;
	y = -1;
	printf("COL:%d\n", all->map->col_count);
	printf("ROW:%d\n", all->map->row_count);
	while (++x < all->map->row_count)
	{
		y = -1;
		while (++y < all->map->col_count)
		{	
				ft_putnbr(all->coordinate->points[x][y]);
				ft_putstr("");
		}
		ft_putstr("\n");
	}
}

void malloc_a_skeleton(t_all *all)
{
	all->map = malloc(sizeof(t_map));
	all->coordinate = malloc(sizeof(t_coordinate));
	all->connection = malloc(sizeof(t_connection));
	all->move_grid = malloc(sizeof(t_move_grid));
}
