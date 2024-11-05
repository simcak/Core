/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:55:14 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/05 23:57:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * MAP RULES
 * - The map must be composed of only 6 possible characters (0 1 2 N S W E)
 * - The map must be closed/surrounded by walls
 * - The map must be parsed as it looks in the file
 * - Spaces are a valid part of the map and are up to us to handle
 */

void	parse_map(t_main *game)
{
	t_map	*map;

	map = game->map;
	printf("Map example: %s\n", map->colors[1]);
}
