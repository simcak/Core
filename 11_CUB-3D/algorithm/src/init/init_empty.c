/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/31 17:11:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_empty_player(t_game *game)
{
	game->player = ft_safe_malloc(sizeof(t_player), ERR_MALL_GAME);

	game->player->x = 0;
	game->player->y = 0;
	game->player->angle = 0;
	game->player->fov_rad = 0;
}

static void	init_empty_ray(t_game *game)
{
	game->ray = ft_safe_malloc(sizeof(t_ray), ERR_MALL_GAME);

	game->ray->angle = 0;
	game->ray->distance = 0;
}

static void init_empty_map(t_game *game)
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
	game->map->txt_no = NULL;
	game->map->txt_so = NULL;
	game->map->txt_we = NULL;
	game->map->txt_ea = NULL;
	game->map->mlx_txt_no = NULL;
	game->map->mlx_txt_so = NULL;
	game->map->mlx_txt_we = NULL;
	game->map->mlx_txt_ea = NULL;
}

/**
 * @brief Initialize empty game struct
 */
void	init_empty(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->animation = NULL;
	game->animation_txt = NULL;
	init_empty_player(game);
	init_empty_ray(game);
	init_empty_map(game);
}
