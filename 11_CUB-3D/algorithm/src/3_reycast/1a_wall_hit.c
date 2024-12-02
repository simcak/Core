/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1a_wall_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:17:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 20:18:04 by psimcak          ###   ########.fr       */
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

/**
 * @brief Calculates the vertical intersection of the ray with a wall.
 */
void	calculate_vertical_hit(t_main *game, t_player *player, t_ray *ray)
{
	bool	facing_north;
	bool	facing_west;
	int		pixel;

	facing_north = ray->angle > 0 && ray->angle < PI_FT;
	facing_west = ray->angle > PI_FT / 2 && ray->angle < 3 * PI05_FT;

	ray->y_step = facing_north ? TILE_SIZE : -TILE_SIZE;
	ray->x_step = TILE_SIZE / tan(ray->angle);
	if ((facing_west && ray->x_step > 0) || (!facing_west && ray->x_step < 0))
		ray->x_step *= -1;

	ray->vhit.y = floor(player->pos.y / TILE_SIZE) * TILE_SIZE;
	ray->vhit.y += facing_north ? TILE_SIZE : 0;
	ray->vhit.x = player->pos.x + (ray->vhit.y - player->pos.y) / tan(ray->angle);

	pixel = facing_north ? -1 : 1;
	while (!wall_hit(game->file->map, ray->vhit.x, ray->vhit.y - pixel))
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
	bool	facing_west;
	bool	facing_north;
	int		pixel;

	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;
	facing_north = ray->angle > 0 && ray->angle < PI_FT;

	ray->x_step = facing_west ? -TILE_SIZE : TILE_SIZE;
	ray->y_step = TILE_SIZE * tan(ray->angle);
	if ((facing_north && ray->y_step < 0) || (!facing_north && ray->y_step > 0))
		ray->y_step *= -1;

	ray->hhit.x = floor(player->pos.x / TILE_SIZE) * TILE_SIZE;
	ray->hhit.x += facing_west ? 0 : TILE_SIZE;
	ray->hhit.y = player->pos.y + (ray->hhit.x - player->pos.x) * tan(ray->angle);

	pixel = facing_west ? 1 : -1;
	while (!wall_hit(game->file->map, ray->hhit.x - pixel, ray->hhit.y))
	{
		ray->hhit.x += ray->x_step;
		ray->hhit.y += ray->y_step;
	}
}
