/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser_zp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:20:02 by zprokop           #+#    #+#             */
/*   Updated: 2024/12/17 16:59:45 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Parses the game .cub file and fill up the game map structure.
 * CALLER: main
 * 
 * This function reads the game configuration (= .cub) file and extracts the
 * necessary information: file content - texture, colors, game map.
 */
void	parser(t_main *game)
{
	parse_load_check_file(game);
	parse_load_check_texture(game, game->file->txt);
	parse_load_check_colors(game, game->file->color);
	parse_load_check_map(game);
}
