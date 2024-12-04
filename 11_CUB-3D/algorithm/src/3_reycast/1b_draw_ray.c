/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:08:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/04 13:18:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	draw_line(t_main *game, int ray_counter, double start, double stop)
{
	while (start < stop)
		mlx_put_pixel(game->image, ray_counter, start++, game->ray->color);
}

/**
 * @brief Get wall parameters
 * 
 * wall->height - ratio times the distance of the wall from the player
 * wall->start - we know the height so we subtract half of it from the center
 * wall->end - same but we add half of the height
 * 
 * texture is chosen based on the orientation of the ray the angles of the ray
 * is circulating CLOCWISE.
 */
static void	get_wall_parameters(t_main *game, t_wall *wall)
{
	wall->height = (TILE_SIZE / game->ray->distance) * ((SWIDTH / 2)
			/ tan(game->player->fov_rad / 2));
	wall->start = (SHEIGHT / 2) - (wall->height / 2);
	if (wall->start < 0)
		wall->start = 0;
	wall->end = (SHEIGHT / 2) + (wall->height / 2);
	if (wall->end > SHEIGHT)
		wall->end = SHEIGHT;
	if (game->ray->orientation == HORISONTAL)
		if (game->ray->angle > PI05_FT && game->ray->angle < 3 * PI05_FT)
			wall->txt = game->file->txt->mlx_txt_we;
	if (game->ray->orientation == HORISONTAL)
		if (game->ray->angle <= PI05_FT || game->ray->angle >= 3 * PI05_FT)
			wall->txt = game->file->txt->mlx_txt_ea;
	if (game->ray->orientation == VERTICAL)
		if (game->ray->angle > 0 && game->ray->angle < PI_FT)
			wall->txt = game->file->txt->mlx_txt_so;
	if (game->ray->orientation == VERTICAL)
		if (game->ray->angle >= PI_FT && game->ray->angle <= 2 * PI_FT)
			wall->txt = game->file->txt->mlx_txt_no;
}

static t_clr	reverse_bytes(t_clr color)
{
	t_clr	reversed_color;

	reversed_color.r = color.a;
	reversed_color.g = color.b;
	reversed_color.b = color.g;
	reversed_color.a = color.r;
	return (reversed_color);
}

/**
 * @brief Draw wall line
 * 
 * txt_x - the x coordinate of the texture - which column line to draw
 * txt_y - the y coordinate of the texture - which row line to draw
 * We need to rotate the colors in the pixel color because the colors are
 * stored like: 0xAABBGGRR and we need to rotate them to 0xRRGGBBAA.
 */
static void	draw_wall_line(t_main *game, int rc, t_wall *wall)
{
	uint32_t	pixel_color;
	double		x;
	double		y;
	double		y_txt_step;

	if (game->ray->orientation == HORISONTAL)
		x = fmod(game->ray->hit.y, TILE_SIZE) * wall->txt->width / TILE_SIZE;
	else if (game->ray->orientation == VERTICAL)
		x = fmod(game->ray->hit.x, TILE_SIZE) * wall->txt->width / TILE_SIZE;
	wall->clr = (t_clr *)wall->txt->pixels;
	y_txt_step = wall->txt->height / wall->height;
	y = ((wall->start - SHEIGHT / 2) + wall->height / 2) * y_txt_step;
	while (wall->start < wall->end)
	{
		pixel_color = reverse_bytes(
				wall->clr[(int)y * wall->txt->width + (int)x]).rgba;
		mlx_put_pixel(game->image, rc, wall->start++, pixel_color);
		y += y_txt_step;
	}
}

void	draw_ray(t_main *game, int ray_counter)
{
	t_wall	*wall;

	wall = game->wall;
	get_wall_parameters(game, wall);
	game->ray->color = game->file->color->c_color;
	draw_line(game, ray_counter, (double)0, wall->start);
	draw_wall_line(game, ray_counter, wall);
	game->ray->color = game->file->color->f_color;
	draw_line(game, ray_counter, wall->end, (double)SHEIGHT);
}
