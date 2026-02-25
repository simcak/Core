#include "life.h"

void	ft_move(t_map *map, char c)
{
	if (c == 'x')
	{
		if (map->writing == 1)
			map->writing = 0;
		else if (map->writing == 0)
			map->writing = 1;
	}
	if (c == 'w')
		map->x--;
	if (c == 's')
		map->x++;
	if (c == 'a')
		map->y--;
	if (c == 'd')
		map->y++;
}

int	lets_play_game(char **av)
{
	t_map	map;
	
	map.writing = 0;
	map.width = atoi(av[1]); map.height = atoi(av[2]); map.gol = atoi(av[3]);
	map.x = 0; map.y = 0;

	/// INIT: grid without allocating
	char	grid[map.height][map.width + 1];
	for (int i = 0, j; i < map.height; ++i)
	{
		for (j = 0; j < map.width ; ++j)
			grid[i][j] = '.';
		grid[i][j] = '\n';
	}

	/// GAME: 1st round
	char	command;
	while (read(STDIN_FILENO, &command, 1) == 1)
	{
		ft_move(&map, command);
		if (map.x < 0 || map.y < 0 || map.x > map.height || map.y > map.width)
			return -1;
		if (map.writing)
			grid[map.x][map.y] = '0';
	}

	/// GAME: loop

	/// PRINT:
	for (int i = 0; i < map.height; ++i)
		for (int j = 0; j <= map.width; ++j)
			putchar(grid[i][j]);

	return 0;
}

int	main(int ac, char **av)
{
	if (ac == 4)
	{
		if(lets_play_game(av) == -1)
			return (write(STDERR_FILENO, "error\n", 6), 1);
	}
	else
	{
		return (write(STDERR_FILENO, "error\n", 6), 1);
	}
	return 0;
}
