/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:55:14 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 15:48:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Calculates the width and height of the map.
 * 
 * 1) Find the longest row in the map.
 * 2) Count the number of rows.
 * 2.1) Skip the empty lines at the end of the map.
 * 3) Store the calculated dimensions in the map structure.
 */
static void	get_measurements(t_main *game, t_map *map)
{
	int	max_width;
	int	line_num;
	int	line_len;

	max_width = 0;
	line_num = -1;
	while (map->grid[++line_num])
	{
		line_len = last_char_index(map->grid[line_num]);
		if (line_len > max_width)
			max_width = line_len;
	}
	map->width = max_width;
	while (line_has_only_spaces(map->grid[--line_num]))
		;
	map->height = line_num + 1;
	printf("Width: %d\nHeight: %d\n", map->width, map->height);
	if (map->width < 3 || map->height < 3)
		safe_exit(game, BR"Map has some problem."RST);
}

/**
 * @brief Looking for the pointer to the first line of the map.
 * The map is stored in the GRID variable.
 *
 * 1) Find the last line of the file.
 * 2) Skip the empty lines at the end of the file.
 * 3) Find the first line that doesn't start with a '1'.
 * 4) Assign the address of the first line of the map to the GRID variable.
 * 5) If the map is not found, print an error message and exit the program.
 * 6) Find the width and height of the map.
 */
static void	find_beginning(t_main *game, t_map *map)
{
	int	startline;
	int	spaces;

	startline = -1;
	while (map->parsed_file[++startline])
		;
	while (line_has_only_spaces(map->parsed_file[--startline]))
		;
	startline++;
	while (--startline)
	{
		spaces = space_counter(map->parsed_file[startline]);
		if (map->parsed_file[startline][spaces] != '1')
			if (map->parsed_file[startline][spaces] != '0')
				break ;
	}
	if (++startline <= 0)
		safe_exit(game, ERR_MAP_NOT_FOUND);
	map->grid = &map->parsed_file[startline];
	get_measurements(game, map);
}

/**
 * @brief Copy the map to a new memory location.
 * 
 * 0) Save the pointer to the old map and set the old map pointer to NULL.
 * 1) Allocate memory for the new map.
 * 2) Copy the map to the new memory location.
 * 3) Fill the empty spaces with ' ' => create a rectangle.
 * 4) Add a NULL pointer at the end of the map.
 * 5) Replace the spaces with '0' - if there is a space IN the map, its OK.
 */
static void	copy_map(t_map *map)
{
	char	**grid_ptr;
	int		i;
	int		line_len;

	grid_ptr = map->grid;
	map->grid = NULL;
	map->grid = ft_smalloc(sizeof(char *) * (map->height + 1), ERR_MGRID);
	i = -1;
	while (++i < map->height)
	{
		line_len = last_char_index(grid_ptr[i]) + 1;
		map->grid[i] = ft_smalloc(sizeof(char) * (map->width + 1), ERR_MGRID);
		ft_strlcpy(map->grid[i], grid_ptr[i], line_len + 1);
		line_len--;
		while (++line_len <= map->width)
			map->grid[i][line_len] = ' ';
		map->grid[i][line_len] = '\0';
	}
	map->grid[i] = NULL;
	ft_replace_char(map->grid, ' ', '0');
}

/**
 * @brief Find the starting position of the player.
 * 
 * 1) Iterate through the map and find the player = 'N', 'S', 'W', 'E'.
 * 		1.1) Save the coordinates of the player.
 * 		1.2) Count the number of players found.
 * 2) Print error message if:
 * 		- Player not found
 * 		- Multiple players found
 */
static void	find_start_position(t_main *game, t_map *map)
{
	int		i;
	int		j;
	int		counter;
	char	*line;

	i = -1;
	counter = 0;
	while (game->map->grid[++i])
	{
		j = -1;
		line = game->map->grid[i];
		while (line[++j])
		{
			if (is_nswe(line[j]))
			{
				map->start_pos.x = j;
				map->start_pos.y = i;
				map->start_pos.nswe = line[j];
				counter++;
			}
		}
	}
	if (counter == 0)
		safe_exit(game, BR"Player (N S W E) not found"RST);
	if (counter > 1)
		safe_exit(game, BR"Multiple players (N S W E) found"RST);
}

static void	check_valid_characters(t_main *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (!is_nswe(map->grid[i][j])
				&& map->grid[i][j] != '0' && map->grid[i][j] != '1')
				safe_exit(game, BR"Invalid character in map"RST);
		}
	}
}

/**
 * @brief Check if the map is surrounded by walls.
 * 
 * 1) Are we out of scope? Does the value exist?
 */
static void	check_walls_around_player(t_main *game, t_map *map, int x, int y)
{
	if (y < 0 || x < 0 || y >= map->height || !map->grid[y][x])
		safe_exit(game, BR"Map is not surrounded by walls"RST);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'X')
		return ;
	else if (map->grid[y][x] == '0' || is_nswe(map->grid[y][x]))
		map->grid[y][x] = 'X';
	check_walls_around_player(game, map, x + 1, y);
	check_walls_around_player(game, map, x - 1, y);
	check_walls_around_player(game, map, x, y + 1);
	check_walls_around_player(game, map, x, y - 1);
}

/**
 * MAP RULES
 * - The map must be composed of only 6 possible characters (0 1 N S W E)
 * - The map must be closed/surrounded by walls
 * - The map must be parsed as it looks in the file
 * - Spaces are a valid part of the map and are up to us to handle
 * - The map is the last element in file (except for the empty lines)
 */

void	parse_load_check_map(t_main *game)
{
	t_map		*map;
	t_player	*player;

	map = game->map;
	player = game->player;
	find_beginning(game, map);
	copy_map(map);
	find_start_position(game, map);
	// checkers // TODO
	check_valid_characters(game, map);
	check_walls_around_player(game, map, map->start_pos.x, map->start_pos.y);
	ft_replace_char(map->grid, 'X', ' ');
	map->grid[map->start_pos.y][map->start_pos.x] = map->start_pos.nswe;
}
