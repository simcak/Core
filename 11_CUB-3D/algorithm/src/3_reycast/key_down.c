/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:17:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/27 04:10:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static bool	can_step_in(t_map *map, int grid_y, int grid_x)
{
	if (map->grid[grid_y][grid_x] == ' ' || is_nswe(map->grid[grid_y][grid_x]))
		return (true);
	return (false);
}

static void	perform_move(t_map *map, t_player *player)
{
	int	new_p_x;
	int	new_p_y;
	int	grid_x;
	int	grid_y;

	new_p_x = round(player->pos.x + player->move.x);
	grid_x = new_p_x / TILE_SIZE;
	grid_y = player->pos.y / TILE_SIZE;
	if (grid_x >= 0 && grid_x < map->width
		&& grid_y >= 0 && grid_y < map->height)
	{
		if (can_step_in(map, grid_y, grid_x))
			player->pos.x = new_p_x;
	}
	new_p_y = round(player->pos.y + player->move.y);
	grid_y = new_p_y / TILE_SIZE;
	grid_x = player->pos.x / TILE_SIZE;
	if (grid_y >= 0 && grid_y < map->height
		&& grid_x >= 0 && grid_x < map->width)
	{
		if (can_step_in(map, grid_y, grid_x))
			player->pos.y = new_p_y;
	}
}

bool	ft_move(t_main *game, int key)
{
	game->player->move.x = 0;
	game->player->move.y = 0;

	if (key == MLX_KEY_W)
	{
		game->player->move.x = cos(game->player->dir.rad) * MOVE_SPEED;
		game->player->move.y = sin(game->player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_S)
	{
		game->player->move.x = -cos(game->player->dir.rad) * MOVE_SPEED;
		game->player->move.y = -sin(game->player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_A)
	{
		game->player->move.x = sin(game->player->dir.rad) * MOVE_SPEED;
		game->player->move.y = -cos(game->player->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_D)
	{
		game->player->move.x = -sin(game->player->dir.rad) * MOVE_SPEED;
		game->player->move.y = cos(game->player->dir.rad) * MOVE_SPEED;
	}
	perform_move(game->file->map, game->player);
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
