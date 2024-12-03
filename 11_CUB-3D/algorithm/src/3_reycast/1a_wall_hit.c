/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_wall_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:17:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/03 19:45:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Checks if the ray hit a wall.
 * 
 */
static bool	wall_hit(t_map *map, double ray_hit_x, double ray_hit_y)
{
	int	m_x;
	int	m_y;

	if (ray_hit_x < 0 || ray_hit_y < 0)
		return (true);
	m_x = floor(ray_hit_x / TILE_SIZE);
	m_y = floor(ray_hit_y / TILE_SIZE);
	if (m_y >= map->height || m_y < 0 || m_x >= map->width || m_x < 0)
		return (true);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (true);
	return (false);
}

// Purpose of this function is just to make the hit calculation more readable.
static void	facing_north_dilema(t_ray *ray)
{
	bool	facing_north;

	facing_north = ray->angle > 0 && ray->angle < PI_FT;
	if (facing_north)
	{
		ray->y_step = TILE_SIZE;
		ray->vhit.y += TILE_SIZE;
		ray->pixel = -1;
	}
	else
	{
		ray->y_step = -TILE_SIZE;
		ray->pixel = 1;
	}
}

// Purpose of this function is just to make the hit calculation more readable.
static void	facing_west_dilema(t_ray *ray)
{
	bool	facing_west;

	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;
	if (facing_west)
	{
		ray->x_step = -TILE_SIZE;
		ray->pixel = 1;
	}
	else
	{
		ray->x_step = TILE_SIZE;
		ray->hhit.x += TILE_SIZE;
		ray->pixel = -1;
	}
}

/**
 * @brief Calculates the vertical intersection of the ray with a wall.
 */
void	calculate_vertical_hit(t_main *game, t_player *player, t_ray *ray)
{
	bool	facing_west;

	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;
	ray->x_step = TILE_SIZE / tan(ray->angle);
	if ((facing_west && ray->x_step > 0) || (!facing_west && ray->x_step < 0))
		ray->x_step *= -1;
	ray->vhit.y = floor(player->pos.y / TILE_SIZE) * TILE_SIZE;
	facing_north_dilema(ray);
	ray->vhit.x = player->pos.x + (ray->vhit.y - player->pos.y)
		/ tan(ray->angle);
	while (!wall_hit(game->file->map, ray->vhit.x, ray->vhit.y - ray->pixel))
	{
		ray->vhit.x += ray->x_step;
		ray->vhit.y += ray->y_step;
	}
}

/**
 * @brief Calculates the horizontal intersection of the ray with a wall.
 */
void	calculate_horizontal_hit(t_main *game, t_player *player, t_ray *ray)
{
	bool	facing_north;

	facing_north = ray->angle > 0 && ray->angle < PI_FT;
	ray->y_step = TILE_SIZE * tan(ray->angle);
	if ((facing_north && ray->y_step < 0) || (!facing_north && ray->y_step > 0))
		ray->y_step *= -1;
	ray->hhit.x = floor(player->pos.x / TILE_SIZE) * TILE_SIZE;
	facing_west_dilema(ray);
	ray->hhit.y = player->pos.y + (ray->hhit.x - player->pos.x)
		* tan(ray->angle);
	while (!wall_hit(game->file->map, ray->hhit.x - ray->pixel, ray->hhit.y))
	{
		ray->hhit.x += ray->x_step;
		ray->hhit.y += ray->y_step;
	}
}
