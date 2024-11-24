/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 20:54:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Initializes the player structure.
 * 
 * After parsing, we have the player's starting position and direction.
 * Based on that we can initialize the player's structure.
 * E and W are opposite directions, same as N and S.
 */
static void	init_player(t_player *player, t_map *map)
{
	if (map->start_pos.nswe == 'E' || map->start_pos.nswe == 'W')
	{
		player->dir.x = (map->start_pos.nswe == 'E') ? 1 : -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = (map->start_pos.nswe == 'E') ? FOV : -FOV;
		player->dir_rad = (map->start_pos.nswe == 'E') ? 0 : M_PI;
	}
	if (map->start_pos.nswe == 'N' || map->start_pos.nswe == 'S')
	{
		player->dir.x = 0;
		player->dir.y = (map->start_pos.nswe == 'S') ? 1 : -1;
		player->plane.x = (map->start_pos.nswe == 'S') ? FOV : -FOV;
		player->plane.y = 0;
		player->dir_rad = (map->start_pos.nswe == 'S') ? M_PI_2 : 3 * M_PI_2;
	}
	player->pos.x = map->start_pos.x + 0.5;
	player->pos.y = map->start_pos.y + 0.5;
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROTATION_SPEED;
	// todo: buff_dist, step_x, step_y
	// maybe delete vectors and use only angles
}

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
