/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:40:59 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 13:21:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief 
 * CALLER: parse_texture
 */
char	*parser_value(char *key, char **parsed_file)
{
	int	i;
	int	j;

	i = -1;
	while (parsed_file[++i])
	{
		j = -1;
		if (ft_strncmp(parsed_file[i], key, ft_strlen(key)) != 0)
			continue ;
		// if condition and other logic for finding the key
		j++;
		return (parsed_file[i]); // temporary return
	}
	return (NULL);
}

/**
 * @brief Parses the texture paths from the parsed file.
 * CALLER: parser
 */
void	parse_load_check_texture(t_main *game, char **parsed_file)
{
	t_map	*map;

	map = game->map;
	map->tx_no = parser_value("NO", parsed_file);
	map->tx_so = parser_value("SO", parsed_file);
	map->tx_we = parser_value("WE", parsed_file);
	map->tx_ea = parser_value("EA", parsed_file);
	if (!map->tx_no || !map->tx_so || !map->tx_we || !map->tx_ea)
		safe_exit(game, BR"Invalid texture path - parser file"RST);
	
	map->mlx_tx_no = mlx_load_png(map->tx_no);
	map->mlx_tx_so = mlx_load_png(map->tx_so);
	map->mlx_tx_we = mlx_load_png(map->tx_we);
	map->mlx_tx_ea = mlx_load_png(map->tx_ea);
	if (!map->mlx_tx_no || !map->mlx_tx_so || !map->mlx_tx_we
		|| !map->mlx_tx_ea)
		safe_exit(game, BR"Invalid texture path - mlx load png"RST);
}

/**
 * @brief Parses the game .cub file and fill up the game map structure.
 * CALLER: main
 * 
 * This function reads the game configuration (= .cub) file and extracts the
 * necessary information: file content - texture, colors, game map.
 * 
 * Deeply in the functions, we have checkers for the validity of the file.
 * - The map must be composed of only 6 possible characters (0 1 2 N S W E)
 * - The map must be closed/surrounded by walls
 * - Except for the map content, each type of element can be separated by one or
    more empty line(s)
 * - Except for the map content which always has to be the last, each type of
    element can be set in any order in the file
 * - Except for the map, each type of information from an element can be
    separated by one or more space(s)
 * - The map must be parsed as it looks in the file
 * - Spaces are a valid part of the map and are up to us to handle
 * - You must be able to parse any kind of map, as long as it respects the rules
    of the map
 */
void	parser(t_main *game)
{
	t_map	*map;

	map = game->map;
	parse_check_file(game);
	for (int i = 0; map->parsed_file[i]; i++) {						// debug
		printf("Parsed file [%i]: %s\n", i, map->parsed_file[i]);
	}
	
	// parse_load_check_texture(game, map->parsed_file); // TODO
	
}