/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:39 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/05 23:54:57 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define ERR_MALL_TXT		BR"Malloc failed for 2D texture setup"RST
#define ERR_MALL_CLR		BR"Malloc failed for 2D color setup"RST

/**
 * Checks if there is ONE flag in the parsed file.
 * If so, it returns the path to the texture.
 * If not, it exits the program.
 */
char	*ft_safe_flag(char *flag, t_main *game, char **parsed_file)
{
	int		line;
	int		flag_count;
	char	*txt_path;

	line = -1;
	flag_count = 0;
	txt_path = NULL;
	while (parsed_file[++line])
	{
		if (we_found_flag(game, flag, line))
		{
			flag_count++;
			txt_path = txt_path_finder(game, flag, line);
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate flag in the parsed file"RST);
	return (txt_path);
}

/**
 * SETUP RULES
 * - Your program must be able to set the floor and ceiling colors to two
   different ones.
 * - Except for the map content, each type of element can be separated by one or
    more empty line(s)
 * - Except for the map content which always has to be the last, each type of
    element can be set in any order in the file
 * - Except for the map, each type of information from an element can be
    separated by one or more space(s)
 * - You must be able to parse any kind of map, as long as it respects the rules
    of the map
 */
void	parse_load_check_setup(t_main *game)
{
	t_map	*map;

	map = game->map;
	map->txt_paths = ft_dalloc(sizeof(char *) * 5, ERR_MALL_TXT);
	map->txt_paths[0] = ft_safe_flag("NO", game, map->parsed_file);
	map->txt_paths[1] = ft_safe_flag("SO", game, map->parsed_file);
	map->txt_paths[2] = ft_safe_flag("WE", game, map->parsed_file);
	map->txt_paths[3] = ft_safe_flag("EA", game, map->parsed_file);
	map->txt_paths[4] = NULL;

	map->colors = ft_dalloc(sizeof(char *) * 3, ERR_MALL_CLR);
	map->colors = (char **) malloc(sizeof(char *) * 3);
	map->colors[0] = ft_safe_flag("F", game, map->parsed_file);
	map->colors[1] = ft_safe_flag("C", game, map->parsed_file);
	map->colors[2] = NULL;
	checker_path_color(game, map->txt_paths);
	checker_path_color(game, map->colors);
}
