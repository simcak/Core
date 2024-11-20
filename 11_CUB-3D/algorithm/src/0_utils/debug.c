/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/20 21:54:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_debug(int type, t_main *game)
{
	if (type == ALL)
	{
		printf(BR"************* DEBUG *************\n"RST);
		for (int i = 0; game->map->parsed_file[i]; i++)
			printf(BW"p-file [%i]:\t| %s\n"RST, i, game->map->parsed_file[i]);
		
		for (int i = 0; i < 4; i++)
			printf(BM"txt_paths[%d]:\t| %s\n"RST, i, game->map->txt_paths[i]);
		
		for (int i = 0; i < 2; i++)
			printf(BY"colors[%d]:\t| %s\n"RST, i, game->map->colors[i]);
		
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_c[%d]:\t| %d\n"RST, i, game->map->rgb_c[i]);
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_f[%d]:\t| %d\n"RST, i, game->map->rgb_f[i]);
		for (int i = 0; game->map->grid[i]; i++)
			printf(BB"Grid [%i]:\t| %s\n"RST, i, game->map->grid[i]);
		printf(BW"Width:\t\t| %d\n"RST, game->map->width);
		printf(BW"Height:\t\t| %d\n"RST, game->map->height);
	}
	printf(BR"*********** END DEBUG ***********\n"RST);
}
