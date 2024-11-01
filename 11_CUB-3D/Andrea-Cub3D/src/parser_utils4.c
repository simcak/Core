/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:46:41 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/29 10:07:38 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Checks the format of the color values in the given array. Exits upon
 * error detected.
 * 
 * @param split_rgb The array of color values to check.
 * @param game The game structure.
 */
void	check_clr_format(char **split_rgb, t_game *game)
{
	int	clr_count;
	int	i;
	int	j;

	clr_count = 0;
	while (split_rgb[clr_count] != NULL)
		clr_count++;
	if (clr_count != 3)
	{
		free_str_arr(split_rgb);
		error_print_exit(ERR_COLOR_FORMAT, game);
	}
	i = -1;
	while (split_rgb[++i] != NULL)
	{
		j = -1;
		while (split_rgb[i][++j] != '\0')
		{
			if (!ft_isdigit(split_rgb[i][j]))
			{
				free_str_arr(split_rgb);
				error_print_exit(ERR_COLOR_FORMAT, game);
			}
		}
	}
}

/**
 * Checks if the given RGB string contains exactly two commas,
 * thus being input in the correct format.
 * If the number of commas is not equal to 2, frees the RGB string and exits
 * the program with an error message.
 *
 * @param rgb The RGB string to check.
 * @param game The game structure.
 */
void	check_for_two_commas(char *rgb, t_game *game)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (rgb[i] != '\0')
	{
		if (rgb[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
	{
		free(rgb);
		error_print_exit(ERR_COLOR_FORMAT, game);
	}
}
