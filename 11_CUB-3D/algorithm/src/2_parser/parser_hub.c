/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:40:59 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/05 23:58:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Parses the game .cub file and fill up the game map structure.
 * CALLER: main
 * 
 * This function reads the game configuration (= .cub) file and extracts the
 * necessary information: file content - texture, colors, game map.
 */
void	parser(t_main *game)
{
	t_map	*map;

	map = game->map;
	parse_check_file(game);

	// debug
	for (int i = 0; map->parsed_file[i]; i++) {
		printf(BG"Parsed file [%i]: %s\n"RST, i, map->parsed_file[i]);
	}
	// debug

	parse_load_check_setup(game);

	// debug
	for (int i = 0; i < 4; i++)
		printf(BB"txt_paths[%d]: %s\n"RST, i, game->map->txt_paths[i]);
	for (int i = 0; i < 2; i++)
		printf(BY"colors[%d]: %s\n"RST, i, game->map->colors[i]);
	// debug

	// parse_map(game); // TODO
}