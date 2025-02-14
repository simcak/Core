/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_key_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:17:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/18 12:03:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Calculate the next position of the player.
 * 
 * Here we calculate the next position of the player and check if the player
 * can step in there.
 * If so, we update the player's position based on the movement vector.
 */
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
 * we send the movement vector to the perform_move function.
 * - sin_f and cos_f are used to safe some lines :) those are input variables
 *   that defines the direction of the movement.
 */
static bool	ft_move(t_main *game, int key, int sin_f, int cos_f)
{
	t_player	*bob;

	bob = game->player;
	if (key == MLX_KEY_W || key == MLX_KEY_UP
		|| key == MLX_KEY_S || key == MLX_KEY_DOWN)
	{
		bob->move.x = cos_f * cos(bob->dir.rad) * MOVE_SPEED;
		bob->move.y = sin_f * sin(bob->dir.rad) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_R)
	{
		bob->move.x = cos(bob->dir.rad) * MOVE_SPEED * 3;
		bob->move.y = sin(bob->dir.rad) * MOVE_SPEED * 3;
	}
	else if (key == MLX_KEY_A || key == MLX_KEY_D)
	{
		bob->move.x = sin_f * sin(bob->dir.rad) * MOVE_SPEED;
		bob->move.y = cos_f * cos(bob->dir.rad) * MOVE_SPEED;
	}
	perform_move(game->file->map, bob);
	return (true);
}

/**
 * @brief Rotates the player's direction.
 * 
 * Here we update the player's direction. It is dependent on the rotation speed.
 * Init direction is dependent on the spawn angle (S N W E).
 * This variable is used in the raycasting algorithm (put_image>ray_cast).
 */
static bool	ft_rotate(t_main *game, double rot_speed, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		keep_in_range(game->player->dir.rad);
		if (game->player->dir.rad < 0)
			game->player->dir.rad += 2 * M_PI;
		else
			game->player->dir.rad -= rot_speed;
		return (true);
	}
	if (key == MLX_KEY_RIGHT)
	{
		keep_in_range(game->player->dir.rad);
		if (game->player->dir.rad > 2 * M_PI)
			game->player->dir.rad -= 2 * M_PI;
		else
			game->player->dir.rad += rot_speed;
		return (true);
	}
	return (false);
}

/**
 * @brief Changes the player's field of view.
 * 
 * The player's field of view is the angle of the player's vision in radians.
 * 
 * Mathematically make more sense to subtract with minus and add fov radians
 * with plus BUT it is more intuitive to do the opposite. Kinda zooming.
 * 
 * We also have a limit of 0.5 and 3 radians - so it doesn't go too wild.
 */
static bool	ft_fov(t_main *game, int key)
{
	if (key == MLX_KEY_KP_ADD)
	{
		if (game->player->fov_rad - 0.1 >= 0.5)
			game->player->fov_rad -= 0.042;
		return (true);
	}
	else if (key == MLX_KEY_KP_SUBTRACT)
	{
		if (game->player->fov_rad + 0.1 <= 3)
			game->player->fov_rad += 0.042;
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		pressed = ft_move(game, MLX_KEY_W, 1, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_R))
		pressed = ft_move(game, MLX_KEY_R, 1, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		pressed = ft_move(game, MLX_KEY_S, -1, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		pressed = ft_move(game, MLX_KEY_A, 1, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		pressed = ft_move(game, MLX_KEY_D, -1, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_KP_SUBTRACT))
		pressed = ft_fov(game, MLX_KEY_KP_SUBTRACT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_KP_ADD))
		pressed = ft_fov(game, MLX_KEY_KP_ADD);
	return (pressed);
}
