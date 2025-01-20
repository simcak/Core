/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parser_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:55:14 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/18 11:31:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Check if the map is surrounded by walls.
 * 
 * 1) Are we out of scope? Does the value exist?
 * 2) If we are on a wall or we have already visited this place, return.
 * 3) If we are on a floor or a player, mark this place as visited ('X').
 * 4) Check the places around the current position - recursively.
 */
static void	check_where_can_we_go(t_main *game, t_map *map, int x, int y)
{
	if (y < 0 || x < 0 || y >= map->height || !map->grid[y][x])
		safe_exit(game, BR"Map is not surrounded by walls"RST);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'X')
		return ;
	else if (map->grid[y][x] == '0' || is_nswe(map->grid[y][x]))
		map->grid[y][x] = 'X';
	check_where_can_we_go(game, map, x + 1, y);
	check_where_can_we_go(game, map, x - 1, y);
	check_where_can_we_go(game, map, x, y + 1);
	check_where_can_we_go(game, map, x, y - 1);
}

/**
 * @brief Check if the map contains only valid characters.
 * 
 * Iterate through the map and check if the character is valid.
 *   - Valid characters: '0', '1', 'N', 'S', 'W', 'E'.
 */
static void	check_valid_characters(t_main *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
			if (!is_nswe(map->grid[i][j])
				&& map->grid[i][j] != '0' && map->grid[i][j] != '1')
				safe_exit(game, BR"Invalid character in map"RST);
	}
}

static void	map_checker(t_main *game, int counter)
{
	if (game->file->map->height < 3)
		safe_exit(game, BR"Invalid map height"RST);
	if (counter == 0)
		safe_exit(game, BR"Player (N S W E) not found"RST);
	if (counter > 1)
		safe_exit(game, BR"Multiple players (N S W E) found"RST);
}

/**
 * @brief Find the starting position of the player.
 * 
 * 1) Iterate through the map and find the player = 'N', 'S', 'W', 'E'.
 *     - Save the coordinates of the player.
 *     - Count the number of players found.
 * 2) Print error message if:
 *     - Player not found
 *     - Multiple players found
 */
static void	find_start_position(t_main *game, t_map *map)
{
	int		i;
	int		j;
	int		counter;

	i = -1;
	counter = 0;
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (is_nswe(map->grid[i][j]))
			{
				map->start_pos.x = j;
				map->start_pos.y = i;
				map->start_pos.nswe = map->grid[i][j];
				counter++;
			}
		}
	}
	map_checker(game, counter);
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
	t_file		*file;
	t_map		*map;

	file = game->file;
	map = game->file->map;
	define_grid(file);
	find_start_position(game, map);
	check_valid_characters(game, map);
	check_where_can_we_go(game, map, map->start_pos.x, map->start_pos.y);
	ft_replace_chars(map->grid, 'X', ' ');
	max_map(map);
	map->grid[map->start_pos.y][map->start_pos.x] = map->start_pos.nswe;
}
