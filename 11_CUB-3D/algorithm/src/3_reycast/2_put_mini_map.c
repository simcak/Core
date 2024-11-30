/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_put_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:35:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/30 13:39:16 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static bool	euclidean_distance(int x, int y, int pos_x, int pos_y)
{
	return (sqrt(pow(x - pos_x, 2) + pow(y - pos_y, 2)) < 2);
}

void	put_mini_map(t_main *game, t_map *map)
{
	int		y;
	int		x;
	int		color;
	int		px;
	int		py;
	int		pos_x;
	int		pos_y;

	y = -1;
	pos_x = floor(game->player->pos.x / TILE_SIZE * MAXI_GRID);
	pos_y = floor(game->player->pos.y / TILE_SIZE * MAXI_GRID);
	while (map->grid_max[++y])
	{
		x = -1;
		while (map->grid_max[y][++x])
		{
			color = map->grid_max[y][x] == ' ' ? WHITE : BLACK;
			color = map->grid_max[y][x] == '8' ? WHITE : color;
			px = x / MINI_MAP;
			color = euclidean_distance(x, y, pos_x, pos_y) ? RED : color;
			while (px < (x + 1) / MINI_MAP)
			{
				py = y / MINI_MAP;
				while (py < (y + 1) / MINI_MAP)
					mlx_put_pixel(game->image, px, py++, (uint32_t)color);
				px++;
			}
		}
	}
}
// todo - resize to the fix size, add rays