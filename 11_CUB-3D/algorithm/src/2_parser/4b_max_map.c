/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4b_max_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:22:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/03 16:05:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Used in max_map function only.
 */
static void	add_corners(t_map *map, int i, int j)
{
	int	sz;

	sz = MAXI_GRID;
	if (i > 0 && j > 0 && map->grid_max[i - 1][j - 1] != '1')
		map->grid_max[i - 1][j - 1] = 'X';
	if (i > 0 && j < map->width * sz - 1 && map->grid_max[i - 1][j + 1] != '1')
		map->grid_max[i - 1][j + 1] = 'X';
	if (i < map->height * sz - 1 && j > 0 && map->grid_max[i + 1][j - 1] != '1')
		map->grid_max[i + 1][j - 1] = 'X';
	if (i < map->height * sz - 1 && j < map->width * sz - 1
		&& map->grid_max[i + 1][j + 1] != '1')
		map->grid_max[i + 1][j + 1] = 'X';
}

/**
 * Used in max_map function only.
 * 
 * 1) 
 */
static void	add_walls(t_map *map)
{
	int	i;
	int	j;
	int	sz;

	i = -1;
	sz = MAXI_GRID;
	while (++i < map->height * sz)
	{
		j = -1;
		while (++j < map->width * (sz + 1))
		{
			if (map->grid_max[i][j] == '1')
			{
				if (i > 0 && map->grid_max[i - 1][j] != '1')
					map->grid_max[i - 1][j] = 'X';
				if (i < map->height * sz - 1 && map->grid_max[i + 1][j] != '1')
					map->grid_max[i + 1][j] = 'X';
				if (j > 0 && map->grid_max[i][j - 1] != '1')
					map->grid_max[i][j - 1] = 'X';
				if (j < map->width * sz - 1 && map->grid_max[i][j + 1] != '1')
					map->grid_max[i][j + 1] = 'X';
				add_corners(map, i, j);
			}
		}
	}
	ft_replace_chars(map->grid_max, 'X', '8');
}

/**
 * @brief Create a 10 times bigger map so we keep distances from walls.
 * 
 * 1) we put 10x character in a row. Char after char.
 * 2) we put 10x row in a column. Row after row.
 * 3) we add 1 layer of walls around the original walls.
 */
void	max_map(t_main *game, t_map *map)
{
	int		i;
	int		j;
	int		k;
	int		l;

	map->grid_max = (char **)ft_dalloc(game, sizeof(char *),
			(map->height * (MAXI_GRID + 1)), BR""ERR_MALL"GRID_MAX"RST);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < MAXI_GRID)
		{
			map->grid_max[i * MAXI_GRID + j] = ft_smalloc(sizeof(char)
					* (map->width * (MAXI_GRID + 1)), BR""ERR_MALL"GRIDMAX"RST);
			k = -1;
			while (++k <= map->width)
			{
				l = -1;
				while (++l < MAXI_GRID)
					map->grid_max[i * MAXI_GRID + j][k * MAXI_GRID + l]
						= map->grid[i][k];
			}
			map->grid_max[i * MAXI_GRID + j][map->width * (MAXI_GRID + 1)] = '\0';
		}
	}
	map->grid_max[map->height * MAXI_GRID] = NULL;
	add_walls(map);
}
