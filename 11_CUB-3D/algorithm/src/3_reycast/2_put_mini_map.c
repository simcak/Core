/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_put_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:35:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/30 19:30:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static bool	euclidean_distance(int x, int y, int pos_x, int pos_y)
{
	return (sqrt(pow(x - pos_x, 2) + pow(y - pos_y, 2)) < 2);
}

static uint32_t	set_color(t_map *map, int x, int y, int pos_x, int pos_y)
{
	uint32_t	color;

	if (y < 0 || x < 0 || y >= map->height * 10 || x >= map->width * 10
		|| !map->grid_max[y] || x >= (int)strlen(map->grid_max[y]))
		return (VOID_COLOR);

	color = map->grid_max[y][x] == ' ' ? WALL_COLOR : VOID_COLOR;
	color = map->grid_max[y][x] == '8' ? WALL_COLOR : color;
	color = euclidean_distance(x, y, pos_x, pos_y) ? PLAYER_COLOR : color;
	return (color);
}

static void	init_mm(t_minimap *mm, t_main *game, int key)
{
	if (key == 1)
	{
		mm->pgx = floor(game->player->pos.x / TILE_SIZE * MAXI_GRID);
		mm->pgy = floor(game->player->pos.y / TILE_SIZE * MAXI_GRID);
		mm->start_x = mm->pgx - MINI_MAP_WIDTH / 2;
		mm->start_y = mm->pgy - MINI_MAP_HEIGHT / 2;
		mm->y = -1;
	}
	if (key == 2)
	{
		mm->grid_x = mm->start_x + mm->x;
		mm->grid_y = mm->start_y + mm->y;
		mm->color = set_color(game->file->map, mm->grid_x, mm->grid_y,
			mm->pgx, mm->pgy);
		mm->py = mm->y * MINI_MAP;
	}
}

static void put_direction_line(t_main *game)
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
		pixel_x = (int)(MINI_MAP_WIDTH / 2 + cos(dir_rad) * i);
		pixel_y = (int)(MINI_MAP_HEIGHT / 2 + sin(dir_rad) * i);
		mlx_put_pixel(game->image, pixel_x, pixel_y, PLAYER_COLOR);
	}
}


/**
 * @brief Put the mini map on the screen.
 */
void	put_mini_map(t_main *game)
{
	t_minimap	mm;

	init_mm(&mm, game, 1);
	while (++mm.y < MINI_MAP_HEIGHT)
	{
		mm.x = -1;
		while (++mm.x < MINI_MAP_WIDTH)
		{
			init_mm(&mm, game, 2);
			while (mm.py < (mm.y + 1) * MINI_MAP)
			{
				mm.px = mm.x * MINI_MAP;
				while (mm.px < (mm.x + 1) * MINI_MAP)
				{
					mlx_put_pixel(game->image, mm.px, mm.py, mm.color);
					mm.px++;
				}
				mm.py++;
			}
		}
	}
	put_direction_line(game);
}