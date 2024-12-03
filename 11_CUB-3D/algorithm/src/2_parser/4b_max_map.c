/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4b_max_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:22:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/03 19:41:35 by psimcak          ###   ########.fr       */
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
}

/**
 * @brief Initialize the grid_max array.
 * 
 * flag 1) Allocate memory for the grid_max array.
 * flag 2) Copy the original grid to the grid_max array.
 */
void	init_maxi_grid(t_map *map, t_maxigrid *mg, int flag)
{
	if (flag == 1)
	{
		map->grid_max[mg->i * MAXI_GRID + mg->j] = ft_smalloc(sizeof(char)
				* (map->width * (MAXI_GRID + 1)), BR""ERR_MALL"GRIDMAX"RST);
	}
	else if (flag == 2)
	{
		mg->l = -1;
		while (++mg->l < MAXI_GRID)
			map->grid_max[mg->i * MAXI_GRID + mg->j][mg->k * MAXI_GRID + mg->l]
				= map->grid[mg->i][mg->k];
	}
	else if (flag == 3)
	{
		mg->x = map->width * (MAXI_GRID + 1);
		mg->y = mg->i * MAXI_GRID + mg->j;
		map->grid_max[mg->y][mg->x] = 0;
	}
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
	t_maxigrid	mg;

	map->grid_max = (char **)ft_dalloc(game, sizeof(char *),
			(map->height * (MAXI_GRID + 1)), BR""ERR_MALL"GRID_MAX"RST);
	mg.i = -1;
	while (++mg.i < map->height)
	{
		mg.j = -1;
		while (++mg.j < MAXI_GRID)
		{
			init_maxi_grid(map, &mg, 1);
			mg.k = -1;
			while (++mg.k <= map->width)
				init_maxi_grid(map, &mg, 2);
			init_maxi_grid(map, &mg, 3);
		}
	}
	map->grid_max[map->height * MAXI_GRID] = NULL;
	add_walls(map);
	ft_replace_chars(map->grid_max, 'X', '8');
}
