/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:40:59 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/20 21:56:40 by psimcak          ###   ########.fr       */
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
	parse_load_check_file(game);
	parse_load_check_texture(game);
	parse_load_check_colors(game);
	parse_load_check_map(game);
}