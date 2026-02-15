/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:59:28 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_orientation(t_player *player, t_map *map)
{
	if (map->start_pos.nswe == 'E' || map->start_pos.nswe == 'W')
	{
		if (map->start_pos.nswe == 'E')
			player->dir.rad = 0;
		else if (map->start_pos.nswe == 'W')
			player->dir.rad = PI_FT;
	}
	else if (map->start_pos.nswe == 'N' || map->start_pos.nswe == 'S')
	{
		if (map->start_pos.nswe == 'N')
			player->dir.rad = 3 * PI05_FT;
		else if (map->start_pos.nswe == 'S')
			player->dir.rad = PI05_FT;
	}
}

/**
 * @brief Initializes the player structure.
 * 
 * After parsing, we have the player's starting position and direction.
 * Based on that we can initialize the player's structure.
 * E and W are opposite directions, same as N and S.
 */
static void	init_player(t_player *player, t_map *map)
{
	player->fov_rad = FOV * PI_FT / 180;
	player->pos.x = 0;
	player->pos.y = 0;
	player->nxt_pos.x = 0;
	player->nxt_pos.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->dir.rad = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->plane.rad = 0;
	player->rot_speed = ROTATION_SPEED;
	player->buff_dist = 0.25;
	player->aspect_ratio = (double)SWIDTH / (double)SHEIGHT;
	init_orientation(player, map);
	player->pos.x = (int)(map->start_pos.x * TILE_SIZE + TILE_SIZE / 2);
	player->pos.y = (int)(map->start_pos.y * TILE_SIZE + TILE_SIZE / 2);
}

/**
 * @brief Initializes the MLX
 * 
 * Initializes image and window so we have place where to draw.
 * We don't allow to resize the window.
 */
static void	init_mlx42(t_main *game)
{
	game->mlx = mlx_init(SWIDTH, SHEIGHT, "cub3D", false);
	if (!game->mlx)
		safe_exit(game, mlx_strerror(mlx_errno));
	game->image = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	if (!(game->image))
		safe_exit(game, mlx_strerror(mlx_errno));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		safe_exit(game, mlx_strerror(mlx_errno));
}

/**
 * @brief Initializes the game structure with default values.
 */
void	init(int type, t_main *game)
{
	if (type == DEFAULT)
		init_default(game);
	else if (type == FILE)
		parser(game);
	else if (type == PLAYER)
		init_player(game->player, game->file->map);
	else if (type == MLX)
		init_mlx42(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
