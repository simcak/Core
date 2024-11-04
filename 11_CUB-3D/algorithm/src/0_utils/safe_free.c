/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:33:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 13:16:56 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	safe_free(t_main *game)
{
	if (game->map)
		free(game->map);
	if (game->map->parsed_file) {
		printf("freeing parsed file\n");
		free(game->map->parsed_file);
	}
	free(game);
}
