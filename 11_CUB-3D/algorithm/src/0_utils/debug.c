/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/20 17:12:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_debug(int type, t_main *game)
{
	if (type == ALL)
	{
		printf(BR"DEBUG\n"RST);
		printf("game->map->fd = %d\n", game->map->fd);

		for (int i = 0; game->map->parsed_file[i]; i++)
			printf(BW"Parsed file [%i]: %s\n"RST, i, game->map->parsed_file[i]);
		
		for (int i = 0; i < 4; i++)
			printf(BB"txt_paths[%d]: %s\n"RST, i, game->map->txt_paths[i]);
		
		for (int i = 0; i < 2; i++)
			printf(BY"colors[%d]: %s\n"RST, i, game->map->colors[i]);
		
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_c[%d]: %d\n"RST, i, game->map->rgb_c[i]);
		for (int i = 0; i < 3; i++)
			printf(BG"rgb_f[%d]: %d\n"RST, i, game->map->rgb_f[i]);
	}
}
