/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_put_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:35:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/30 16:56:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

// static bool	euclidean_distance(int x, int y, int pos_x, int pos_y)
// {
// 	return (sqrt(pow(x - pos_x, 2) + pow(y - pos_y, 2)) < 2);
// }

// static int	set_color(char **grid, int x, int y, int pos_x, int pos_y)
// {
// 	int		color;

// 	color = grid[y][x] == ' ' ? WHITE : BLACK;
// 	color = grid[y][x] == '8' ? WHITE : color;
// 	color = euclidean_distance(x, y, pos_x, pos_y) ? RED : color;
// 	return (color);
// }

// void	put_mini_map(t_main *game, t_map *map)
// {
// 	int		y;
// 	int		x;
// 	int		color;
// 	int		px;
// 	int		py;
// 	int		pos_x;
// 	int		pos_y;

// 	y = -1;
// 	pos_x = floor(game->player->pos.x / TILE_SIZE * MAXI_GRID);
// 	pos_y = floor(game->player->pos.y / TILE_SIZE * MAXI_GRID);
// 	while (map->grid_max[++y])
// 	{
// 		x = -1;
// 		while (map->grid_max[y][++x])
// 		{
// 			color = set_color(map->grid_max, x, y, pos_x, pos_y);
// 			px = x;
// 			while (px < (x + 1))
// 			{
// 				py = y;
// 				while (py < (y + 1))
// 					mlx_put_pixel(game->image, px, py++, (uint32_t)color);
// 				px++;
// 			}
// 		}
// 	}
// }
// todo - resize to the fix size, add rays

static bool	euclidean_distance(int x, int y, int pos_x, int pos_y)
{
	return (sqrt(pow(x - pos_x, 2) + pow(y - pos_y, 2)) < 2);
}

static int	set_color(t_map *map, int x, int y, int pos_x, int pos_y)
{
	int color;

	// Default to void color if out of bounds
	if (y < 0 || x < 0 || y >= map->height * 10 || x >= map->width * 10
		|| !map->grid_max[y] || x >= (int)strlen(map->grid_max[y]))
		return VOID_COLOR;

	color = map->grid_max[y][x] == ' ' ? WALL_COLOR : VOID_COLOR;
	color = map->grid_max[y][x] == '8' ? WALL_COLOR : color;
	color = euclidean_distance(x, y, pos_x, pos_y) ? PLAYER_COLOR : color;
	return color;
}

void	put_mini_map(t_main *game, t_map *map)
{
	int x, y, px, py;
	int color;
	int player_grid_x, player_grid_y;
	int start_x, start_y;

	player_grid_x = floor(game->player->pos.x / TILE_SIZE * MAXI_GRID);
	player_grid_y = floor(game->player->pos.y / TILE_SIZE * MAXI_GRID);

	// Calculate the top-left corner of the minimap to keep player in center
	start_x = player_grid_x - MINI_MAP_WIDTH / 2;
	start_y = player_grid_y - MINI_MAP_HEIGHT / 2;

	for (y = 0; y < MINI_MAP_HEIGHT; y++)
	{
		for (x = 0; x < MINI_MAP_WIDTH; x++)
		{
			int grid_x = start_x + x;
			int grid_y = start_y + y;

			color = set_color(map, grid_x, grid_y, player_grid_x, player_grid_y);

			// Drawing scaled tile on minimap
			for (py = y * MINI_MAP; py < (y + 1) * MINI_MAP; py++)
			{
				for (px = x * MINI_MAP; px < (x + 1) * MINI_MAP; px++)
				{
					mlx_put_pixel(game->image, px, py, (uint32_t)color);
				}
			}
		}
	}
}