/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:59:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/02 16:31:10 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_debug(int type, t_main *game)
{
	if (type == ALL)
	{
		printf(BR"DEBUG\n"RST);
		printf("game->map->fd = %d\n", game->map->fd);
	}
}
