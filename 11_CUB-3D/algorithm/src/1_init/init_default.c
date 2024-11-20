/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/20 17:39:11 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
# define ERR_MALL_MAP		BR"Memory allocation failed for map"RST

static void init_default_map(t_main *game)
{
	game->map = ft_safe_malloc(sizeof(t_map), ERR_MALL_MAP);

	game->map->fd = 0;
	game->map->parsed_file = NULL;
	game->map->txt_paths = NULL;
	game->map->colors = NULL;
	game->map->rgb_raw = NULL;
	game->map->rgb_c = NULL;
	game->map->rgb_f = NULL;
	game->map->grid = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->start_count = 0;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->start_dir = '\0';
	game->map->mlx_txt_no = NULL;
	game->map->mlx_txt_so = NULL;
	game->map->mlx_txt_we = NULL;
	game->map->mlx_txt_ea = NULL;
}

/**
 * @brief Initialize default game struct
 */
void	init_default(t_main *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->animation = NULL;
	game->animation_txt = NULL;
	game->player = NULL;
	game->ray = NULL;
	init_default_map(game);
}
