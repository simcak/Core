/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/05 23:53:57 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
 * @brief Checks if the flag is in the parsed file.
 * CALLER: ft_safe_flag
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
 * CALLER: ft_safe_flag
 */
char	*txt_path_finder(t_main *game, char *flag, int line)
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
 * @brief Checks if there are any duplications or empty values in parsed file.
 * CALLER: parse_load_check_setup
 */
void	checker_path_color(t_main *game, char **txt_paths)
{
	int	i;
	int	j;

	i = -1;
	while (txt_paths[++i])
	{
		j = i;
		while (txt_paths[++j])
		{
			if (strlen(txt_paths[j]) == 0)
				safe_exit(game, BR"Empty value in the parsed file"RST);
			if (ft_strncmp(txt_paths[i], txt_paths[j],
				ft_strlen(txt_paths[i])) == 0)
				safe_exit(game, BR"Duplicate value in the parsed file"RST);
		}
	}
}
