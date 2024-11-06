/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:33:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/06 18:04:48 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	two_d_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		printf("freeing arr[%d] = %s\n", i, arr[i]);
		free(arr[i]);
	}
	free(arr);
}

void	safe_free(t_main *game)
{
	if (game->map->parsed_file)
		two_d_free(game->map->parsed_file);
	if (game->map->txt_paths)
		two_d_free(game->map->txt_paths);
	if (game->map->colors)
		two_d_free(game->map->colors);
		// free(game->map->colors);
	if (game->map)
		free(game->map);
	free(game);
}
