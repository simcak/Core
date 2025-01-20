/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:55:13 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3D.h"

// void	ft_debug(int type, t_main *game)
// {
// 	printf(BY"************* DEBUG *************\n"RST);
// 	if (type == ALL)
// 	{
// 		for (int i = 0; game->file->parsed_file[i]; i++)
// 			printf(BW"p-file [%i]:\t| %s\n"RST, i, game->file->parsed_file[i]);
// 		for (int i = 0; i < 4; i++)
// 			printf(BM"txt_paths[%d]:\t| %s\n"RST, i, game->file->txt->paths[i]);
// 		for (int i = 0; i < 2; i++)
// 			printf(BY"colors[%d]:\t| %s\n"RST, i, game->file->color->colors[i]);
// 		for (int i = 0; i < 3; i++)
// 			printf(BG"rgb_c[%d]:\t| %d\n"RST, i, game->file->color->rgb_c[i]);
// 		for (int i = 0; i < 3; i++)
// 			printf(BG"rgb_f[%d]:\t| %d\n"RST, i, game->file->color->rgb_f[i]);
// 		for (int i = 0; game->file->map->grid[i]; i++)
// 			printf(BB"Grid [%i]:\t| %s\n"RST, i, game->file->map->grid[i]);
// 		printf(BY"Width, Height:\t|  %d, %d\n"RST,
// 			game->file->map->width, game->file->map->height);
// 		printf(BY"X, Y, Pos:    \t| [%d, %d] - %c\n"RST,
// 			game->file->map->start_pos.x, game->file->map->start_pos.y,
// 			game->file->map->start_pos.nswe);
// 		printf(BW"Player Pos X: \t| %f\n"RST, game->player->pos.x);
// 		printf(BW"Player Pos Y: \t| %f\n"RST, game->player->pos.y);
// 		printf(BW"Rot Speed:    \t| %f\n"RST, game->player->rot_speed);
// 		// for (int i = 0; game->file->map->grid_max[i]; i++)
// 		// 	printf("%s\n", game->file->map->grid_max[i]);
// 	}
// 	else if (type == MAP)
// 	{
// 		for (int i = 0; game->file->map->grid[i]; i++)
// 		{
// 			for (int j = 0; game->file->map->grid[i][j]; j++)
// 				if (is_nswe(game->file->map->grid[i][j]))
// 					printf(BR"%c"RST, game->file->map->grid[i][j]);
// 				else
// 					printf(BB"%c"RST, game->file->map->grid[i][j]);
// 			printf("\n");
// 		}
// 		printf(BW"Width, Height:  \t|  %d, %d\n"RST,
// 			game->file->map->width, game->file->map->height);
// 		printf(BW"Start X, Y      \t| [%d, %d]\n"RST,
// 			game->file->map->start_pos.x, game->file->map->start_pos.y);
// 	}
// 	else if (type == MAXI_MAP)
// 		for (int i = 0; game->file->map->grid_max[i]; i++)
// 			printf("%s\n", game->file->map->grid_max[i]);
// 	printf(BY"*********** END DEBUG ***********\n"RST);
// }
