/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_utils_zp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:39:07 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 17:00:32 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Colors must be different for ceiling and floor.
 */
void	difference_check(t_main *game, int *rgb_c, int *rgb_f)
{
	if (rgb_c[0] == rgb_f[0] && rgb_c[1] == rgb_f[1] && rgb_c[2] == rgb_f[2])
		safe_exit(game, BR"Ceiling and floor colors must be different"RST);
}

int	ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_rgb(t_main *game, int *rgb)
{
	free(rgb);
	free_str_arr(game->file->color->rgb_raw);
	safe_exit(game, BR"RGB values must be in range <0-255>"RST);
}
