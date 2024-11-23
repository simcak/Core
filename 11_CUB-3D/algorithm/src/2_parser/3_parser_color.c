/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parser_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:01 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 16:10:31 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * With this function we find the pointer to the rgb values in the parsed file.
 * It skips the flag and the spaces after the flag.
 * Benefit of pointer returner is that we dont allocate memory for this.
 */
static char	*rgb_start_finder(t_main *game, char *flag, int line)
{
	char	**parsed_file;
	int		flag_len;
	int		spaces_1;
	int		spaces_2;

	parsed_file = game->map->parsed_file;
	spaces_1 = space_counter(parsed_file[line]);
	flag_len = ft_strlen(flag);
	spaces_2 = space_counter(parsed_file[line] + spaces_1 + flag_len);
	return (parsed_file[line] + spaces_1 + flag_len + spaces_2);
}

/**
 * Function to check if the flag is present in the parsed file.
 * It returns the pointer to the start of the RGB values after the flag.
 */
static char	*color_assign(char *flag, t_main *game, char **parsed_file)
{
	int		line;
	int		flag_count;
	char	*rgb;

	line = -1;
	flag_count = 0;
	rgb = NULL;
	while (parsed_file[++line])
	{
		if (we_found_flag(game, flag, line))
		{
			flag_count++;
			rgb = rgb_start_finder(game, flag, line);
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing color flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate color flag in the parsed file"RST);
	return (rgb);
}

/**
 * Function to check if there is only one number per color.
 * It is tolerating the spaces between the numbers.
 * On the input we have one color bumber in string format (e.g. " 255   "").
 * It exits if there are more than one number.
 */
static void	format_check(t_main *game, char *rgb)
{
	int	i;
	int	num_counter;

	i = 0;
	num_counter = 0;
	are_spaces_or_digits(game, rgb);
	while (rgb[i])
	{
		i += space_counter(rgb + i);
		while (is_digit(rgb[i]))
			i++;
		num_counter++;
		if (num_counter > 1)
			safe_exit(game, ERR_RGB_COUNT);
		i += space_counter(rgb + i);
	}
}

/**
 * Function splits the rgb values and checks:
 * - if the values are digits or spaces
 * - if there is only one value per color
 * **************** than we do atoi **************** *
 * - if the values are in range 0-255
 * - if there are 3 values
 */
static int	*split_check_rgb(t_main *game, char *color)
{
	int		*rgb;
	int		i;

	game->map->rgb_raw = ft_split(color, ',');
	rgb = ft_dalloc(sizeof(int *), 3, ERR_MALL_RGB);
	i = -1;
	while (game->map->rgb_raw[++i])
	{
		format_check(game, game->map->rgb_raw[i]);
		rgb[i] = ft_atoi(game->map->rgb_raw[i]);
		range_check(game, rgb[i]);
	}
	if (i != 3)
		safe_exit(game, BR"RGB values must be 3"RST);
	return (rgb);
}

/**
 * COLOR RULES
 * - Your program must be able to set the floor and ceiling colors to two
   different ones.
 * - The three different colors are in RGB format.
  * - Except for the map content, each type of element can be separated by one or
    more empty line(s)
 * - Except for the map content which always has to be the last, each type of
    element can be set in any order in the file
 * - Except for the map, each type of information from an element can be
    separated by one or more space(s)
 * - You must be able to parse any kind of map, as long as it respects the rules
    of the map
 */
void	parse_load_check_colors(t_main *game)
{
	game->map->colors = ft_dalloc(sizeof(char *), 3, ERR_MALL_CLR);
	game->map->colors[0] = color_assign("F", game, game->map->parsed_file);
	game->map->colors[1] = color_assign("C", game, game->map->parsed_file);
	game->map->colors[2] = NULL;

	game->map->rgb_c = split_check_rgb(game, game->map->colors[0]);
	game->map->rgb_f = split_check_rgb(game, game->map->colors[1]);
	difference_check(game, game->map->rgb_c, game->map->rgb_f);
}
