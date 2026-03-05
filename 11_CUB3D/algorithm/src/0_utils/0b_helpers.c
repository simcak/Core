/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0b_helpers_zp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:07:54 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:54:49 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_isspace(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

bool	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

/**
 * Function to count the spaces till the first non-space character.
 */
int	space_counter(char *input)
{
	int	counter;

	counter = -1;
	while (input[++counter])
		if (!ft_isspace(input[counter]))
			break ;
	return (counter);
}

/**
 * Function to check if the line contains only spaces.
 */
bool	line_has_only_spaces(char *line)
{
	return (space_counter(line) == (int)ft_strlen(line));
}

/**
 * Function to check if the input string contains only spaces or digits.
 */
void	are_spaces_or_digits(t_main *game, char *rgb)
{
	int	i;

	i = -1;
	while (rgb[++i])
	{
		if (ft_isspace(rgb[i]) || ft_isdigit(rgb[i]))
			continue ;
		else
		{
			free_str_arr(game->file->color->rgb_raw);
			safe_exit(game, BR"Non-space or non-digit value detected"RST);
		}
	}
}
