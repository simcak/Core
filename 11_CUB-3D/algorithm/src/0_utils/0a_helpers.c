/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0a_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:02:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/04 15:28:15 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Finds the index of the last non-space character in the input string.
 *
 * @return The index of the last non-space character, or -1 if no non-space
 * character is found.
 */
int	last_char_index(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	if (i < 0)
		return (0);
	return (i);
}

bool	is_nswe(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/**
 * Replaces all occurrences of character c1 with character c2 in the input str.
 */
void	ft_replace_chars(char **line, char c1, char c2)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (line[i][j] == c1)
				line[i][j] = c2;
		}
	}
}

/**
 * @brief Checks if the player can step into the given coordinates.
 * 
 * We check it on a grid_max, which is a 10x bigger grid with extra layer of
 * walls.
 */
bool	can_step_in(t_map *map, int y, int x)
{
	if (map->grid_max[y][x] != '1' && map->grid_max[y][x] != '8')
		return (true);
	return (false);
}

/**
 * @brief Calculates the distance between two points.
 * 
 * formula: sqrt((x1 - x2)^2 + (y1 - y2)^2)
 */
double	euclidean_distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}
