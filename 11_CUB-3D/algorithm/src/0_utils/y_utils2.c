/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:20:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 14:18:23 by psimcak          ###   ########.fr       */
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
	while (i >= 0 && is_space(str[i]))
		i--;
	if (i < 0)
		return (0);
	return (i);
}

bool	is_nswe(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	ft_replace_char(char **line, char c1, char c2)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == c1)
				line[i][j] = c2;
			j++;
		}
		i++;
	}
}
