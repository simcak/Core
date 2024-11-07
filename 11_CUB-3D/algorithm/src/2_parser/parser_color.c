/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:01 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/07 18:07:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#define ERR_MALL_CLR		BR"Malloc failed for 2D color setup"RST

static bool	is_space(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

static int	space_counter(char *input)
{
	int	counter;

	counter = -1;
	while (input[++counter])
		if (!is_space(input[counter]))
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
			rgb = rgb_finder(game, flag, line);	// TODO
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing color flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate color flag in the parsed file"RST);
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
	// ft_dupliempty_color(game, game->map->colors);	// TODO
	/* todo: parse and check rgb values - colors */
}