/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:09:10 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 13:15:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Special version of ft_split that splits a string on a '\n' character but
 * preserves it in the result.
 * The input full_string is a content of .cub file.
 * Result is an array of strings, each string is a line from the file.
 * Therefore "parsed file".
*/
static char	**ft_parsed_file(char *full_str, int line_counter)
{
	char	**parsed_file;
	int		line_start;
	int		line_end;
	int		line_len;
	int		i;

	parsed_file = (char **) malloc(sizeof(char *) * (line_counter + 1));
	line_start = 0;
	line_end = 0;
	i = -1;
	if (!parsed_file)
		return (NULL);
	while (++i < line_counter)
	{
		while (full_str[line_end] && full_str[line_end] != '\n')
			line_end++;
		line_len = line_end - line_start;
		parsed_file[i] = ft_substr(full_str, line_start, line_len);
		line_start = line_end + 1;
		line_end += 1;
	}
	parsed_file[i] = NULL;
	return (parsed_file);
}

/**
 * Parses the .cub file and checks its validity.
 * 1) Reads the file line by line and joins them into one long string.
 * 2) Parses the string (file content) into an array of strings.
 * 3) Calls file_checker to check the validity of the parsed file.
 * CALLER: parser
 * 
 * We dont have to free line because it is not allocated if the file is empty.
 */
void	parse_check_file(t_main *game)
{
	char	*line;
	char	*joined;
	char	*tmp_f_content;
	int		line_counter;

	line = ft_get_next_line(game->map->fd);
	tmp_f_content = ft_strdup("");
	line_counter = 0;
	while (line)
	{
		joined = ft_strjoin(tmp_f_content, line);
		free(line);
		free(tmp_f_content);
		tmp_f_content = joined;
		line = ft_get_next_line(game->map->fd);
		line_counter++;
	}
	close(game->map->fd);
	game->map->parsed_file = ft_parsed_file(tmp_f_content, line_counter);
	free(tmp_f_content);
	// file_checker(); // TODO
}
