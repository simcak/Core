/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2a_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 16:10:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define ERR_MALL_TXT		BR"Malloc failed for texture path setup"RST

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
 * In here, there is one potential controversial thing. If there is something
 * after the texture path, it exit. This is because the subject does not specify
 * that we should be benevolent and ignore the garbage after the texture path.
 * = "each type of ELEMENT can be SEPARATED".
 * I insist that this parsing is enough if not correct.
 */
char	*txt_path_finder(t_main *game, char *flag, int line)
{
	char	**parsed_file;
	int		flag_len;
	int		spaces_1;
	int		spaces_2;
	char	*txt_path_start;
	char	*post_txt_path;

	parsed_file = game->map->parsed_file;
	spaces_1 = space_counter(parsed_file[line]);
	flag_len = ft_strlen(flag);
	spaces_2 = space_counter(parsed_file[line] + spaces_1 + flag_len);
	txt_path_start = parsed_file[line] + spaces_1 + flag_len + spaces_2;
	post_txt_path = txt_path_start + char_counter(txt_path_start);
	if (post_txt_path[0] != '\0')
		safe_exit(game, BR"Some garbage after the texture path"RST);
	return (txt_path_start);
}
