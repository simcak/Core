/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:08:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 13:46:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	draw_line(t_main *game, int ray_counter, double start, double stop)
{
	while (start < stop)
		mlx_put_pixel(game->image, ray_counter, start++, game->ray->color);
}

// explaint the math behind this = TODO
static void	get_wall_parameters(t_main *game, t_wall *wall)
{
	wall->height = (TILE_SIZE / game->ray->distance) * ((SWIDTH / 2)
			/ tan(game->player->fov_rad / 2));
	wall->start = (SHEIGHT / 2) - (wall->height / 2);
	wall->start = wall->start < 0 ? 0 : wall->start;
	wall->end = (SHEIGHT / 2) + (wall->height / 2);
	wall->end = wall->end > SHEIGHT ? SHEIGHT : wall->end;
}

void	draw_ray(t_main *game, int ray_counter)
{
	t_wall			*wall;

	wall = game->wall;
	get_wall_parameters(game, wall);
	game->ray->color = game->file->color->c_color;
	draw_line(game, ray_counter, (double)0, wall->start);
	if (game->ray->orientation == HORISONTAL)
		if (game->ray->angle > PI05_FT && game->ray->angle < 3 * PI05_FT)
			game->ray->color = (uint32_t)0x000000FF;
	if (game->ray->orientation == HORISONTAL)
		if (game->ray->angle <= PI05_FT || game->ray->angle >= 3 * PI05_FT)
			game->ray->color = (uint32_t)0x333333FF;
	if (game->ray->orientation == VERTICAL)
		if (game->ray->angle > 0 && game->ray->angle < PI_FT)
			game->ray->color = (uint32_t)0x111111FF;
	if (game->ray->orientation == VERTICAL)
		if (game->ray->angle >= PI_FT && game->ray->angle <= 2 * PI_FT)
			game->ray->color = (uint32_t)0x222222FF;
	draw_line(game, ray_counter, wall->start, wall->end);	// draw texture
	// draw_wall(game, ray_counter, wall, txt);
	game->ray->color = game->file->color->f_color;
	draw_line(game, ray_counter, wall->end, (double)SHEIGHT);
}
