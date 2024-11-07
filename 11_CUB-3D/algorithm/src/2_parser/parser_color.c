/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:01 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/07 19:08:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#define ERR_MALL_CLR		BR"Malloc failed for 2D color setup"RST
#define ERR_MALL_RGB		BR"Malloc failed for 2D rgb setup"RST
#define ERR_RGB				BR"RGB values must be digits in range 0-255\n\
Format: e.c. '255,5,42' - rgb setup is ONE information."RST

static bool	ft_is_space(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

static bool ft_is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

static int	space_counter(char *input)
{
	int	counter;

	counter = -1;
	while (input[++counter])
		if (!ft_is_space(input[counter]))
			break ;
	return (counter);
}

/**
 * 
 */
char	*rgb_finder(t_main *game, char *flag, int line)
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
 * 
 */
static char	*ft_safe_color(char *flag, t_main *game, char **parsed_file)
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
			rgb = rgb_finder(game, flag, line);
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing color flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate color flag in the parsed file"RST);
	return (rgb);
}

static char	**split_check_rgb(t_main *game, char *color)
{
	char	**rgb;
	int		i;
	int		j;

	rgb = ft_split(color, ',');
	i = -1;
	while (rgb[++i])
	{
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_is_digit(rgb[i][j]))
				safe_exit(game, BR ERR_RGB RST);
		}
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
	game->map->colors[0] = ft_safe_color("F", game, game->map->parsed_file);
	game->map->colors[1] = ft_safe_color("C", game, game->map->parsed_file);
	game->map->colors[2] = NULL;

	game->map->rgb_c = split_check_rgb(game, game->map->colors[0]);
	game->map->rgb_f = split_check_rgb(game, game->map->colors[1]);
	
	/* todo: parse and check rgb values - colors */
}