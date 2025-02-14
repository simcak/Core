/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_put_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:35:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/18 11:59:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Set the color of the pixel based on its meaning.
 * 
 * Based on the position of the pixel, we set the color of the pixel.
 */
static uint32_t	set_color(t_map *map, int x, int y, t_minimap *mm)
{
	uint32_t	color;

	if (y < 0 || x < 0 || y >= map->height * 10 || x >= map->width * 10
		|| !map->grid_max[y] || x >= (int)strlen(map->grid_max[y]))
		return (VOID_COLOR);
	color = VOID_COLOR;
	if (map->grid_max[y][x] == ' ')
		color = WALL_COLOR;
	else if (map->grid_max[y][x] == '8')
		color = WALL_COLOR;
	if (euclidean_distance(x, y, mm->pgx, mm->pgy) < 2)
		color = PLAYER_COLOR;
	return (color);
}

/**
 * @brief Initialize the mini map.
 * 
 * Based on the key, we assign specific values to the mini map struct.
 * It is just a helper function for the put_mini_map function.
 */
static void	init_mm(t_minimap *mm, t_main *game, int key)
{
	if (key == 1)
	{
		mm->pgx = floor(game->player->pos.x / TILE_SIZE * MAXI_GRID);
		mm->pgy = floor(game->player->pos.y / TILE_SIZE * MAXI_GRID);
		mm->width = SWIDTH / 4.2;
		mm->height = SHEIGHT / 4.2;
		mm->start_x = mm->pgx - mm->width / 2;
		mm->start_y = mm->pgy - mm->height / 2;
		mm->y = -1;
	}
	if (key == 2)
	{
		mm->grid_x = mm->start_x + mm->x;
		mm->grid_y = mm->start_y + mm->y;
		mm->color = set_color(game->file->map, mm->grid_x, mm->grid_y, mm);
	}
}

/**
 * @brief Put the direction line on the screen.
 * 
 * We take direction, set the line length, and calculate end position of line.
 * Than, in a loop, we print the line(s) on the screen.
 * If condition just checks if the pixel is within the mini map.
 */
static void	put_direction_line(t_main *game, t_minimap *mm)
{
	int		line_length;
	double	dir_rad;
	int		pixel_x;
	int		pixel_y;
	int		i;

	i = -1;
	line_length = 7;
	dir_rad = game->player->dir.rad;
	while (++i < line_length)
	{
		pixel_x = (int)(mm->width / 2 + cos(dir_rad) * i);
		pixel_y = (int)(mm->height / 2 + sin(dir_rad) * i);
		if (pixel_x >= 0 && pixel_x < mm->width
			&& pixel_y >= 0 && pixel_y < mm->height)
		{
			mlx_put_pixel(game->image, pixel_x, pixel_y, PLAYER_COLOR);
			mlx_put_pixel(game->image, pixel_x + 1, pixel_y + 1, PLAYER_COLOR);
		}
	}
}

/**
 * @brief Put the mini map on the screen.
 * 
 * We go through the whole mini map and set the color of each pixel.
 * 1) We calculate the player's position on the mini map (pgx, pgy) - init 1
 * 2) Calculate the start position of the mini map (start_x, start_y) - init 1
 * 3) We go through the whole mini map and set the color of each pixel.
 * - from position <0, 0> till <mm->width, mm->height>
 * char by char, line by line.
 * 4) For each pixel we calculate the color based on its meaning - init 2
 * - if it is a (added) wall, (walkable) floor, void, or player.
 * 5) We put the pixel on the screen.
 * 6) We put the direction line on the screen.
 */
void	put_mini_map(t_main *game)
{
	t_minimap	mm;

	init_mm(&mm, game, 1);
	while (++mm.y < mm.height)
	{
		mm.x = -1;
		while (++mm.x < mm.width)
		{
			init_mm(&mm, game, 2);
			mlx_put_pixel(game->image, mm.x, mm.y, mm.color);
		}
		mlx_put_pixel(game->image, mm.x, mm.y, VOID_COLOR);
	}
	mm.x = -1;
	while (++mm.x <= mm.width + 1)
		mlx_put_pixel(game->image, mm.x, mm.y, VOID_COLOR);
	put_direction_line(game, &mm);
}
