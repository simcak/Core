/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:17:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/29 17:50:53 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static bool	can_step_in(t_map *map, int y, int x)
{
	if (map->grid[y][x] != '1')
		return (true);
	return (false);
}

static void	perform_move(t_map *map, t_player *player)
{
	double	next_pos_x;
	double	next_pos_y;
	double	grid_x;
	double	grid_y;

	next_pos_x = player->pos.x + player->move.x;
	grid_x = next_pos_x / TILE_SIZE;
	grid_y = player->pos.y / TILE_SIZE;
	if (can_step_in(map, (int)grid_y, (int)grid_x))
		player->pos.x = next_pos_x;

	next_pos_y = player->pos.y + player->move.y;
	grid_y = next_pos_y / TILE_SIZE;
	grid_x = player->pos.x / TILE_SIZE;
	if (can_step_in(map, (int)grid_y, (int)grid_x))
		player->pos.y = next_pos_y;
}

/**
 * @brief Moves the player in the direction of the player's angle.
 * 
 * Here we calculate the MOVEMENT vector.
 */
bool	ft_move(t_main *game, int key)
{
	t_player	*player;

	player = game->player;
	if (key == MLX_KEY_W || key == MLX_KEY_UP)
	{
		player->move.x = cos(player->dir.rad) * MOVE_SPEED;
		player->move.y = sin(player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_R)
	{
		player->move.x = cos(player->dir.rad) * MOVE_SPEED * 3;
		player->move.y = sin(player->dir.rad) * MOVE_SPEED * 3;
	}
	else if (key == MLX_KEY_S || key == MLX_KEY_DOWN)
	{
		player->move.x = -cos(player->dir.rad) * MOVE_SPEED;
		player->move.y = -sin(player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_A)
	{
		player->move.x = sin(player->dir.rad) * MOVE_SPEED;
		player->move.y = -cos(player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_D)
	{
		player->move.x = -sin(player->dir.rad) * MOVE_SPEED;
		player->move.y = cos(player->dir.rad) * MOVE_SPEED;
	}
	perform_move(game->file->map, player);
	return (true);
}

bool	ft_rotate(t_main *game, double rot_speed, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		game->player->dir.rad -= rot_speed;
		if (game->player->dir.rad < 0)
			game->player->dir.rad += 2 * M_PI;
		return (true);
	}
	if (key == MLX_KEY_RIGHT)
	{	
		game->player->dir.rad += rot_speed;
		if (game->player->dir.rad > 2 * M_PI)
			game->player->dir.rad -= 2 * M_PI;
		return (true);
	}
	return (false);
}
