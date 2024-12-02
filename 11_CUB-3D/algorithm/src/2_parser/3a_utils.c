/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:39:07 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 20:08:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Function to check if the rgb values are in the range 0-255.
 */
void	range_check(t_main *game, int rgb)
{
	if (rgb >= 0 && rgb <= 255)
		return ;
	else
		safe_exit(game, BR"RGB values must be in range <0-255>"RST);
}

/**
 * Colors must be different for ceiling and floor.
 */
void	difference_check(t_main *game, int *rgb_c, int *rgb_f)
{
	if (rgb_c[0] == rgb_f[0] && rgb_c[1] == rgb_f[1] && rgb_c[2] == rgb_f[2])
		safe_exit(game, BR"Ceiling and floor colors must be different"RST);
}
