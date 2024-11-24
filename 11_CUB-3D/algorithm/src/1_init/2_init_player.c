/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:47:29 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 12:10:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Initializes the player structure.
 * 
 * After parsing, we have the player's starting position and direction.
 * Based on that we can initialize the player's structure.
 * E and W are opposite directions, same as N and S.
 * - 2 vectors are shared and 2 are the opposite.
 */
void	init_player(t_player *player, t_map *map)
{
	if (map->start_pos.nswe == 'E' || map->start_pos.nswe == 'W')
	{
		player->dir_x = (map->start_pos.nswe == 'E') ? 1 : -1;
		player->dir_y = 0;
		player->cam_x = 0;
		player->cam_y = (map->start_pos.nswe == 'E') ? 0.5 : -0.5;
	}
	if (map->start_pos.nswe == 'N' || map->start_pos.nswe == 'S')
	{
		player->dir_x = 0;
		player->dir_y = (map->start_pos.nswe == 'S') ? 1 : -1;
		player->cam_x = (map->start_pos.nswe == 'S') ? 0.5 : -0.5;
		player->cam_y = 0;
	}
	player->pos_x = map->start_pos.x + 0.5;
	player->pos_y = map->start_pos.y + 0.5;
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROTATION_SPEED;
	// todo: fov_rad, angle, buff_dist, aspec_ratio, step_x, step_y
}
