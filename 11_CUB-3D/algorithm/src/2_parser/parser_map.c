/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:55:14 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/21 15:57:26 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Looking for the pointer to the first line of the map.
 * The map is stored in the GRID variable.
 *
 * 1) Find the last line of the file.
 * 2) Skip the empty lines at the end of the file.
 * 3) Find the first line that doesn't start with a '1'.
 * 4) Assign the address of the first line of the map to the GRID variable.
 * 5) If the map is not found, print an error message and exit the program.
 */
static void	find_beginning(t_map *map, t_main *game)
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
}

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
	if (map->width < 3 || map->height < 3)
		safe_exit(game, BR"Map is not detected."RST);
}

/**
 * @brief Copy the map to a new memory location.
 * 
 * 0) Save the pointer to the old map and set the old map pointer to NULL.
 * 1) Allocate memory for the new map.
 * 2) Copy the map to the new memory location.
 * 3) Fill the empty spaces with ' ' => create a rectangle.
 * 4) Add a NULL pointer at the end of the map.
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
}

/**
 * @brief Check if the map is surrounded by walls on the top and bottom.
 * 
 * 1) Check the first line of the map (and skip the spaces).
 * 1.1) If there is '1' or a space, continue.
 * 2) Check the last line of the map (and skip the spaces).
 * 2.1) If there is '1' or a space, continue.
 */
static void	check_wall_top_bottom(t_map *map, t_main *game)
{
	char	*first_line;
	char	*last_line;
	int		i;

	first_line = map->grid[0];
	i = space_counter(first_line) - 1;
	while (first_line[++i] != '\0')
	{
		if (first_line[i] != '1' && !is_space(first_line[i]))
			safe_exit(game, ERR_WALL"top"RST);
	}
	last_line = map->grid[map->height - 1];
	i = space_counter(last_line) - 1;
	while (last_line[++i] != '\0')
	{
		if (last_line[i] != '1' && !is_space(last_line[i]))
			safe_exit(game, ERR_WALL"bottom"RST);
	}
}

static void	check_wall_left_right(t_map *map, t_main *game)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (++i < (map->height - 1))
	{
		line = map->grid[i];
		j = space_counter(line);
		if (line[j] != '1')
			safe_exit(game, ERR_WALL"left"RST);
		k = last_char_index(line);
		if (k - j <= 1)
			safe_exit(game, BR"Map is not width enough at some line."RST);
		if (line[k] != '1')
			safe_exit(game, ERR_WALL"right"RST);
	}
}

/**
 * MAP RULES
 * - The map must be composed of only 6 possible characters (0 1 2 N S W E)
 * - The map must be closed/surrounded by walls
 * - The map must be parsed as it looks in the file
 * - Spaces are a valid part of the map and are up to us to handle
 * - The map is the last element in file (except for the empty lines)
 */

void	parse_load_check_map(t_main *game)
{
	t_map	*map;

	map = game->map;
	find_beginning(map, game);
	get_measurements(game, map);
	copy_map(map);
	// checkers // TODO
	check_wall_top_bottom(map, game);
	check_wall_left_right(map, game);
}
