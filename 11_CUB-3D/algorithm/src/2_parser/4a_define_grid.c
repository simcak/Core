/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4a_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:18:14 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/03 15:18:30 by psimcak          ###   ########.fr       */
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
	if (map->width < 3 || map->height < 3)
		safe_exit(game, BR"Map has some problem."RST);
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
	map->grid = ft_smalloc(sizeof(char *) * (map->height + 1),
			BR""ERR_MALL"GRID"RST);
	i = -1;
	while (++i < map->height)
	{
		line_len = last_char_index(grid_ptr[i]) + 1;
		map->grid[i] = ft_smalloc(sizeof(char) * (map->width + 1),
				BR""ERR_MALL"GRID"RST);
		ft_strlcpy(map->grid[i], grid_ptr[i], line_len + 1);
		line_len--;
		while (++line_len <= map->width)
			map->grid[i][line_len] = ' ';
		map->grid[i][line_len] = '\0';
	}
	map->grid[i] = NULL;
	ft_replace_chars(map->grid, ' ', '0');
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
void	define_grid(t_main *game, t_file *file)
{
	int	startline;
	int	spaces;

	startline = -1;
	while (file->parsed_file[++startline])
		;
	while (line_has_only_spaces(file->parsed_file[--startline]))
		;
	startline++;
	while (--startline)
	{
		spaces = space_counter(file->parsed_file[startline]);
		if (file->parsed_file[startline][spaces] != '1')
			if (file->parsed_file[startline][spaces] != '0')
				break ;
	}
	if (++startline <= 0)
		safe_exit(game, BR"No valid map found in provided file."RST);
	file->map->grid = &file->parsed_file[startline];
	get_measurements(game, file->map);
	copy_map(file->map);
}
