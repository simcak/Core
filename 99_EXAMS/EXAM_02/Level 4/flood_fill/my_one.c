/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:03:58 by psimcak           #+#    #+#             */
/*   Updated: 2024/01/09 15:45:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flood_fill.h"

void	recursive_fill(char **map, t_point max, char seed, t_point location)
{
	if (location.x < 0 || location.y < 0
		|| location.x >= max.x || location.y >= max.y 
		|| map[location.y][location.x] != seed)
		return;
	
	map[location.y][location.x] = 'F';
	recursive_fill(map, max, seed, (t_point){location.x - 1, location.y});
	recursive_fill(map, max, seed, (t_point){location.x + 1, location.y});
	recursive_fill(map, max, seed, (t_point){location.x, location.y - 1});
	recursive_fill(map, max, seed, (t_point){location.x, location.y + 1});
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	recursive_fill(tab, size, tab[begin.x][begin.y], begin);
}

// void	fill(char **tab, t_point size, t_point begin, char to_fill)
// {
// 	if (begin.y < 0 || begin.y >= size.y || begin.x < 0 || begin.x >= size.x
// 		|| tab[begin.y][begin.x] != to_fill)
// 		return;

// 	tab[begin.y][begin.x] = 'F';
// 	fill(tab, size, (t_point){begin.x - 1, begin.y}, to_fill);
// 	fill(tab, size, (t_point){begin.x + 1, begin.y}, to_fill);
// 	fill(tab, size, (t_point){begin.x, begin.y - 1}, to_fill);
// 	fill(tab, size, (t_point){begin.x, begin.y + 1}, to_fill);
// }

// void	flood_fill(char **tab, t_point size, t_point begin)
// {
// 	fill(tab, size, begin, tab[begin.y][begin.x]);
// }
