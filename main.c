#include "fdf.h"

#define sign(x) ((x>0)?1:((x<0)?-1:0))

void bres_general(int x1, int y1, int x2, int y2, t_connection *connection)
{
  int dx; 
  int dy; 
  int x; 
  int y; 
  int d; 
  int s1; 
  int s2;
  int swap;
  int temp;
  int i;
  swap = 0;

  dx = abs(x2 - x1);
  dy = abs(y2 - y1);
  s1 = sign(x2 - x1);
  s2 = sign(y2 - y1);

  /* Check if dx or dy has a greater range */
  /* if dy has a greater range than dx swap dx and dy */
  if(dy > dx)
  {
  	temp = dx;
  	dx = dy;
  	dy = temp;
  	swap = 1;
  }

  /* Set the initial decision parameter and the initial point */
  d = 2 * dy - dx;
  x = x1;
  y = y1;

  i = 0;
  while (++i <= dx)
  {
    mlx_pixel_put(connection->mlx, connection->win, y, x, GREEN);
    while(d >= 0) 
    {
      if(swap) x = x + s1;
      else 
      {
        y = y + s2;
        d = d - 2 * dx;
      }
    }
    if (swap)
    	y = y + s2;
    else
    	x = x + s1;
    d = d + 2 * dy;
  }
}


 void rotate_x(t_coordinate *coordinate, int y, int z, t_move_grid *grid)
 {
 	float cosa;
 	float sina;

 	printf("%f\n", grid->x_radians);
 	
        cosa = cos(grid->x_radians);
        sina = sin(grid->x_radians);
        coordinate->temp_y = y * cosa - z * sina;
        coordinate->temp_z = y * sina + z * cosa;
 }

void rotate_y(t_coordinate *coordinate, t_move_grid *grid)
{
 	float cosa;
 	float sina;

 	printf("%f\n", grid->y_radians);
 
        cosa = cos(grid->y_radians);
        sina = sin(grid->y_radians);
	coordinate->temp_z = coordinate->temp_z * cosa - coordinate->temp_x * sina;
	coordinate->temp_x = coordinate->temp_z * sina + coordinate->temp_x * cosa;
 }
       
void rotate_z(t_coordinate *coordinate, t_move_grid *grid)
{
 	float cosa;
 	float sina;

 		
        cosa = cos(grid->z_radians);
        sina = sin(grid->z_radians);
        coordinate->temp_x = coordinate->temp_x * cosa + coordinate->temp_y * sina;
        coordinate->temp_y = coordinate->temp_x * sina + coordinate->temp_y * cosa;

    }
        
 
    void project(t_coordinate *coordinate, t_connection *connection, t_map *map)
    {
    	float factor;

  		factor = 400 / (40 - coordinate->temp_z);
        coordinate->temp_x = coordinate->temp_x * factor + ((SCREEN_WIDTH / 2) - (map->col_count));
        coordinate->temp_y = coordinate->temp_y * factor + ((SCREEN_HEIGHT / 2) - (map->row_count));
        mlx_pixel_put(connection->mlx, connection->win, coordinate->temp_y, coordinate->temp_x, GREEN);
    }

    void rotate_all(t_map *map, t_coordinate *coordinate, t_move_grid *grid, t_connection *connection)
    {
    	int x; 
    	int y;
    	int z;
    	
    	z = -1;
    	x = -1;
    	y = -1;
    while (++y < map->col_count)
	{
		x = -1;
		while (++x < map->row_count)
		{	
			z = coordinate->points[x][y];
			coordinate->temp_x = x;
				rotate_x(coordinate, y, z, grid);
				rotate_y(coordinate, grid);
				rotate_z(coordinate, grid);
				project(coordinate, connection, map);

		}
	
	}
}
 
        

int my_funct(int keycode, t_all *all)
{


	
	if (keycode == 53)
		error_master5000("GOODBYE WORLD!");
	if (keycode == 8)
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		if (keycode == 0)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->x_radians += 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);
	
		}
		if (keycode == 1)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->x_radians -= 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);

		}

		if (keycode == 2)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->y_radians += 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);
	
		}
		if (keycode == 3)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->y_radians -= 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);

		}
		if (keycode == 4)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->z_radians += 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);
	
		}
		if (keycode == 5)
		{
		  mlx_clear_window(all->connection->mlx, all->connection->win);
		  all->move_grid->z_radians -= 0.1;
		  rotate_all(all->map, all->coordinate, all->move_grid, all->connection);

		}
	printf("%d\n", keycode);
	return(0);
}

void mlx_connections(t_all *all)
{
	all->connection->mlx = mlx_init();
	all->connection->win = mlx_new_window(all->connection->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "EXAMPLE");
 	mlx_key_hook(all->connection->win, my_funct, all);
	mlx_loop(all->connection->mlx);
}


int main(int ac, char **av)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	malloc_a_skeleton(all);
	if(ac == 2 && av[1])
	{
		all->move_grid->x_radians = 0.0;
		all->move_grid->y_radians = 0.0;
		all->move_grid->z_radians = 0.0;
		all->move_grid->zoom = 10;
		all->move_grid->fov = 5;

		get_file_length(av, all->map);
		read_file(av, all->map,  all->coordinate);
		print_coordinates(all);
		mlx_connections(all);
	}
	else
		error_master5000("Uhmm.. You need a file");

	

	return 0;
}
