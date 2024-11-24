/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 20:04:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_debug(int type, t_main *game)
{
	printf(BR"************* DEBUG *************\n"RST);
	if (type == ALL)
	{
		
		for (int i = 0; game->file->parsed_file[i]; i++)
			printf(BW"p-file [%i]:\t| %s\n"RST, i, game->file->parsed_file[i]);
		
		for (int i = 0; i < 4; i++)
			printf(BM"txt_paths[%d]:\t| %s\n"RST, i, game->file->txt->paths[i]);
		
		for (int i = 0; i < 2; i++)
			printf(BY"colors[%d]:\t| %s\n"RST, i, game->file->color->colors[i]);
		
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_c[%d]:\t| %d\n"RST, i, game->file->color->rgb_c[i]);
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_f[%d]:\t| %d\n"RST, i, game->file->color->rgb_f[i]);
		for (int i = 0; game->file->map->grid[i]; i++)
			printf(BB"Grid [%i]:\t| %s\n"RST, i, game->file->map->grid[i]);
		printf(BY"Width, Height:\t|  %d, %d\n"RST,
			game->file->map->width, game->file->map->height);
		printf(BY"X, Y, Pos:    \t| [%d, %d] - %c\n"RST,
			game->file->map->start_pos.x, game->file->map->start_pos.y,
			game->file->map->start_pos.nswe);
		printf(BW"Player Dir X: \t| %f\n"RST, game->player->dir.x);
		printf(BW"Player Dir Y: \t| %f\n"RST, game->player->dir.y);
		printf(BW"Player Cam X: \t| %f\n"RST, game->player->plane.x);
		printf(BW"Player Cam Y: \t| %f\n"RST, game->player->plane.y);
		printf(BW"Player Pos X: \t| %f\n"RST, game->player->pos.x);
		printf(BW"Player Pos Y: \t| %f\n"RST, game->player->pos.y);
		printf(BW"Move Speed:   \t| %f\n"RST, game->player->move_speed);
		printf(BW"Rot Speed:    \t| %f\n"RST, game->player->rot_speed);
	}
	else if (type == MAP)
	{
		// ft_replace_chars(game->file->map->grid, '0', ' ');
		for (int i = 0; game->file->map->grid[i]; i++)
		{
			for (int j = 0; game->file->map->grid[i][j]; j++)
				if (is_nswe(game->file->map->grid[i][j]))
					printf(BR"%c"RST, game->file->map->grid[i][j]);
				else
					printf(BB"%c"RST, game->file->map->grid[i][j]);
			printf("\n");
		}
		printf(BW"Width, Height:  \t|  %d, %d\n"RST,
			game->file->map->width, game->file->map->height);
		printf(BW"Start X, Y      \t| [%d, %d]\n"RST,
			game->file->map->start_pos.x, game->file->map->start_pos.y);
	}
	printf(BR"*********** END DEBUG ***********\n"RST);
}
