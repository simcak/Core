/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/06 00:01:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_default_player(t_main *game)
{
	game->player = ft_safe_malloc(sizeof(t_player), ERR_MALL_GAME);

	game->player->x = 0;
	game->player->y = 0;
	game->player->angle = 0;
	game->player->fov_rad = 0;
}

static void	init_default_ray(t_main *game)
{
	game->ray = ft_safe_malloc(sizeof(t_ray), ERR_MALL_GAME);

	game->ray->angle = 0;
	game->ray->distance = 0;
}

static void init_default_map(t_main *game)
{
	game->map = ft_safe_malloc(sizeof(t_map), ERR_MALL_MAP);

	game->map->fd = 0;
	game->map->parsed_file = NULL;
	game->map->grid = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->start_count = 0;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->start_dir = '\0';
	game->map->txt_paths = NULL;
	game->map->colors = NULL;
	game->map->mlx_tx_no = NULL;
	game->map->mlx_tx_so = NULL;
	game->map->mlx_tx_we = NULL;
	game->map->mlx_tx_ea = NULL;
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
	init_default_player(game);
	init_default_ray(game);
	init_default_map(game);
}
