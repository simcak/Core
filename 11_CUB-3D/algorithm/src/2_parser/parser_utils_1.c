/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/06 16:37:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define ERR_MALL_TXT		BR"Malloc failed for texture path setup"RST

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

static int	char_counter(char *input)
{
	int	counter;

	counter = -1;
	while (input[++counter])
		if (is_space(input[counter]))
			break ;
	return (counter);
}

/**
 * @brief Checks if the flag is in the parsed file.
 * CALLER: ft_safe_texture
 */
bool	we_found_flag(t_main *game, char *flag, int line)
{
	char	**parsed_file;
	int		flag_len;
	int		spaces;

	parsed_file = game->map->parsed_file;
	spaces = space_counter(parsed_file[line]);
	flag_len = ft_strlen(flag);
	if (ft_strncmp(parsed_file[line] + spaces, flag, flag_len) == 0
			&& is_space(parsed_file[line][spaces + flag_len]))
		return (true);
	return (false);
}

/**
 * @brief Finds the path to the texture in the parsed file.
 * CALLER: ft_safe_texture
 */
char	*txt_path_finder(t_main *game, char *flag, int line)
{
	char	**parsed_file;
	int		flag_len;
	int		spaces_1;
	int		spaces_2;
	char	*txt_path;
	char	*txt_path_start;
	int		txt_path_len;

	parsed_file = game->map->parsed_file;
	spaces_1 = space_counter(parsed_file[line]);
	flag_len = ft_strlen(flag);
	spaces_2 = space_counter(parsed_file[line] + spaces_1 + flag_len);
	txt_path_start = parsed_file[line] + spaces_1 + flag_len + spaces_2;
	txt_path_len = char_counter(txt_path_start) + 1;
	txt_path = ft_safe_malloc(txt_path_len + 1, ERR_MALL_TXT);
	ft_strlcpy(txt_path, txt_path_start, txt_path_len);
	return (txt_path);
}
