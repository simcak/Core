/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_ray_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:25:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 13:47:12 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Keeps an angle in the range [0, 2*PI].
 * CALLED: ray_cast, ft_rotate
 *
 * If the angle is less than 0, it adds 2*PI to shift it to the [0, 2*PI] range.
 * If the angle is more than 2*PI, it subtracts 2*PI to shift it
 * to the [0, 2*PI] range = 360 degrees = [0, 6.283185] range.
 */
double	keep_in_range(double angle)
{
	angle = angle < 0 ? angle + 2 * PI_FT : angle;
	angle = angle > 2 * PI_FT ? angle - 2 * PI_FT : angle;
	return (angle);
}

/**
 * @brief Calculates the distance between two points.
 * 
 * formula: sqrt((rx - px)^2 + (ry - py)^2)
 * 
 * @param px - player's x coordinate
 * @param py - player's y coordinate
 * @param rx - ray's x coordinate
 * @param ry - ray's y coordinate
 */
static double	distance(double px, double py, double rx, double ry)
{
	return (sqrt(pow(rx - px, 2) + pow(ry - py, 2)));
}

/**
 * @brief Picks the shorter ray between the vertical and horizontal rays.
 * 
 * 1.1) Calculates the distance between the player's position and the v-hit.
 * 1.2) Calculates the distance between the player's position and the h-hit.
 */
static void	pick_shorter_ray(t_player *p, t_ray *ray)
{
	double	v_distance;
	double	h_distance;

	v_distance = distance(p->pos.x, p->pos.y, ray->vhit.x, ray->vhit.y);
	h_distance = distance(p->pos.x, p->pos.y, ray->hhit.x, ray->hhit.y);
	if (h_distance < v_distance)
	{
		ray->orientation = HORISONTAL;
		ray->distance = h_distance;
		ray->hit.x = ray->hhit.x;
		ray->hit.y = ray->hhit.y;
	}
	else
	{
		ray->orientation = VERTICAL;
		ray->distance = v_distance;
		ray->hit.x = ray->vhit.x;
		ray->hit.y = ray->vhit.y;
	}
}

/**
 * @brief Casts rays from the player's position in 3D.
 * CALLED: put_image
 *
 * It first sets the initial ray angle to the player's angle minus half
 * of the field of view.
 * 
 * Then, for each column of the screen, it normalizes the ray angle,
 * calculates the vertical and horizontal intersections of the ray with a wall,
 * and selects the shortest ray. It then draws the 3D projection of the wall
 * on the screen.
 * 
 * Finally, it increments the ray angle by the field of view divided
 * by the screen width and repeats the process for the next column.
 */
void	ray_cast(t_main *game, t_player *player, t_ray *ray)
{
	int		ray_counter;
	double	raw_ray_angle;

	ray_counter = -1;
	raw_ray_angle = player->dir.rad - (player->fov_rad / 2);
	while (++ray_counter < SWIDTH)
	{
		ray->angle = keep_in_range(raw_ray_angle);
		calculate_vertical_hit(game, player, ray);
		calculate_horizontal_hit(game, player, ray);
		pick_shorter_ray(player, ray);
		ray->angle_diff = keep_in_range(raw_ray_angle - player->dir.rad);
		game->ray->distance *= cos(ray->angle_diff);
		draw_ray(game, ray_counter);
		raw_ray_angle += player->fov_rad / SWIDTH;
	}
}
