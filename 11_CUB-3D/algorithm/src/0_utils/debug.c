/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 17:20:19 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_debug(int type, t_main *game)
{
	if (type == ALL)
	{
		printf(BR"************* DEBUG *************\n"RST);
		
		for (int i = 0; game->file->parsed_file[i]; i++)
			printf(BW"p-file [%i]:\t| %s\n"RST, i, game->file->parsed_file[i]);
		
		for (int i = 0; i < 4; i++)
			printf(BM"txt_paths[%d]:\t| %s\n"RST, i, game->txt->paths[i]);
		
		for (int i = 0; i < 2; i++)
			printf(BY"colors[%d]:\t| %s\n"RST, i, game->color->colors[i]);
		
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_c[%d]:\t| %d\n"RST, i, game->color->rgb_c[i]);
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_f[%d]:\t| %d\n"RST, i, game->color->rgb_f[i]);
		for (int i = 0; game->map->grid[i]; i++)
			printf(BB"Grid [%i]:\t| %s\n"RST, i, game->map->grid[i]);
		printf(BW"Width:\t\t| %d\n"RST, game->map->width);
		printf(BW"Height:\t\t| %d\n"RST, game->map->height);
		printf(BW"Start Pos:   \t| %c\n"RST, game->map->start_pos.nswe);
		printf(BW"Player Dir X:\t| %f\n"RST, game->player->dir_x);
		printf(BW"Player Dir Y:\t| %f\n"RST, game->player->dir_y);
		printf(BW"Player Cam X:\t| %f\n"RST, game->player->cam_x);
		printf(BW"Player Cam Y:\t| %f\n"RST, game->player->cam_y);
		printf(BW"Player Pos X:\t| %f\n"RST, game->player->pos_x);
		printf(BW"Player Pos Y:\t| %f\n"RST, game->player->pos_y);
	}
	printf(BR"*********** END DEBUG ***********\n"RST);
}
