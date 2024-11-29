/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_key_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:17:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/29 20:45:11 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	perform_move(t_map *map, t_player *player)
{
	double	next_pos_x;
	double	next_pos_y;
	double	grid_x;
	double	grid_y;

	next_pos_x = player->pos.x + player->move.x;
	grid_x = next_pos_x / TILE_SIZE * 10;
	grid_y = player->pos.y / TILE_SIZE * 10;
	if (can_step_in(map, (int)grid_y, (int)grid_x))
		player->pos.x = next_pos_x;

	next_pos_y = player->pos.y + player->move.y;
	grid_y = next_pos_y / TILE_SIZE * 10;
	grid_x = player->pos.x / TILE_SIZE * 10;
	if (can_step_in(map, (int)grid_y, (int)grid_x))
		player->pos.y = next_pos_y;
}

/**
 * @brief Moves the player in the direction of the player's angle.
 * 
 * Here we calculate the MOVEMENT vector.
 */
static bool	ft_move_leftright(t_main *game, int key)
{
	t_player	*player;

	player = game->player;
	if (key == MLX_KEY_A)
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

/**
 * @brief Moves the player in the direction of the player's angle.
 * 
 * Here we calculate the MOVEMENT vector.
 */
static bool	ft_move_updown(t_main *game, int key)
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
	perform_move(game->file->map, player);
	return (true);
}

/**
 * @brief Rotates the player's direction.
 */
static bool	ft_rotate(t_main *game, double rot_speed, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		keep_in_range(game->player->dir.rad);
		game->player->dir.rad = game->player->dir.rad < 0 ?
			game->player->dir.rad + 2 * M_PI :
			game->player->dir.rad - rot_speed;
		return (true);
	}
	if (key == MLX_KEY_RIGHT)
	{	
		game->player->dir.rad = game->player->dir.rad > 2 * M_PI ?
			game->player->dir.rad - 2 * M_PI :
			game->player->dir.rad + rot_speed;
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if the human pressed any of the movement keys (not escape).
 * CALLED: game_loop
 * 
 * We used bool logic to prevent puting the img when the player isn't moving.
 */
bool	key_down_crossroad(t_main *game)
{
	bool	pressed;

	pressed = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		pressed = ft_rotate(game, game->player->rot_speed, MLX_KEY_LEFT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		pressed = ft_rotate(game, game->player->rot_speed, MLX_KEY_RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		pressed = ft_move_updown(game, MLX_KEY_W);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		pressed = ft_move_updown(game, MLX_KEY_W);
	if (mlx_is_key_down(game->mlx, MLX_KEY_R))
		pressed = ft_move_updown(game, MLX_KEY_R);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		pressed = ft_move_updown(game, MLX_KEY_DOWN);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		pressed = ft_move_updown(game, MLX_KEY_S);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		pressed = ft_move_leftright(game, MLX_KEY_A);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		pressed = ft_move_leftright(game, MLX_KEY_D);
	return (pressed);
}
