/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:20:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 19:56:49 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_space(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

bool	is_digit(char c)
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
		if (!is_space(input[counter]))
			break ;
	return (counter);
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
		if (is_space(rgb[i]) || is_digit(rgb[i]))
			continue ;
		else
			safe_exit(game, BR"Non-space or non-digit value detected"RST);
	}
}

/**
 * Function to check if the line contains only spaces.
 */
bool	line_has_only_spaces(char *line)
{
	return (space_counter(line) == (int)ft_strlen(line));
}
