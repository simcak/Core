/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:42 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/29 13:09:39 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Special version of ft_split that splits a string on a newline
 * character but preserves a newline character following the one the split was
 * done on.
 * 
 * @param	full_string	parsed file
 * @param	height		height of the map
 * @return	char**		file splitted on newlines
*/
static char	**ft_split_file(char *full_string, int height)
{
	int		i;
	int		end;
	int		start;
	char	**split_file;

	i = 0;
	end = 0;
	start = 0;
	split_file = (char **) malloc(sizeof(char *) * (height + 1));
	if (!split_file)
		return (NULL);
	while (i < height)
	{
		while (full_string[end] && full_string[end] != '\n')
			end++;
		split_file[i] = ft_substr(full_string, start, end - start);
		start = end + 1;
		end += 1;
		i++;
	}
	split_file[i] = NULL;
	return (split_file);
}

/**
 * @brief Parses a file and stores its contents in the game's map structure.
 * 
 * This function reads the file line by line using the `get_next_line` function
 * and concatenates each line into a single string. The concatenated string is
 * then split into an array of strings using the `ft_split` function and the
 * newline symbol as the delimiter. The resulting array is stored in the
 * `parsed_file` field of the game's map structure.
 * 
 * @param game A pointer to the game structure.
 * @return 0 on success.
 */
static int	file_parser(t_game *game)
{
	char	*line;
	char	*concat;
	char	*temp;
	int		i;

	line = get_next_line(game->map->fd);
	temp = ft_strdup("");
	i = 0;
	while (line)
	{
		concat = ft_strjoin(temp, line);
		free(temp);
		free(line);
		temp = concat;
		line = get_next_line(game->map->fd);
		i++;
	}
	close(game->map->fd);
	game->map->parsed_file = ft_split_file(temp, i);
	free(temp);
	return (0);
}

/**
 * @brief Finds the map in the parsed file and assigns it to the grid pointer.
 *
 * This function searches for the map in the parsed file by iterating backwards
 * from the end of the file. It skips any trailing empty lines and then looks
 * for the first line that doesn't start with a '1' (excluding leading
 * whitespaces) — the previous line thus being the first line of the map.
 * Once the map is found, it assigns the address of the map's starting line to
 * the grid pointer. If the map is not found, it prints an error message and
 * exits the program.
 *
 * @param map The map structure.
 * @param game The game structure.
 */
static void	find_map_in_file(t_map *map, t_game *game)
{
	int	map_start;
	int	j;

	map_start = 0;
	while (map->parsed_file[map_start] != NULL)
		map_start++;
	map_start--;
	while (line_has_spaces_only(map->parsed_file[map_start]))
		map_start--;
	while (map_start >= 0)
	{
		j = 0;
		j = increment_if_space(map->parsed_file[map_start], j);
		if (map->parsed_file[map_start][j] != '1')
			break ;
		map_start--;
	}
	map_start++;
	if (map_start <= 0)
		error_print_exit(ERR_MAP_NOT_FOUND, game);
	map->grid = &map->parsed_file[map_start];
}

/**
 * @brief Parses the game configuration file and initializes the game map.
 * 
 * This function reads the game configuration file and extracts the necessary
 * information such as texture paths, colors, and the game map.
 * It calls various helper functions to parse different sections of the file
 * and store the extracted values in the map struct. If any required values
 * are missing or invalid, it prints an error message and exits the program.
 * 
 * @param game A pointer to the game struct.
 * @return 0 on success.
 */
int	parser(t_game *game)
{
	t_map	*map;

	file_parser(game);
	checker_duplicates(game);
	map = game->map;
	map->txt_no = value_parser("NO", map->parsed_file);
	map->txt_so = value_parser("SO", map->parsed_file);
	map->txt_we = value_parser("WE", map->parsed_file);
	map->txt_ea = value_parser("EA", map->parsed_file);
	if (!map->txt_no || !map->txt_so || !map->txt_we || !map->txt_ea)
		error_print_exit(ERR_MISSING_VALUE, game);
	load_and_verify_textures(game);
	clr_parser("F", map->parsed_file, game);
	clr_parser("C", map->parsed_file, game);
	find_map_in_file(map, game);
	get_map_dimensions(map);
	copy_map(map, game);
	if (map->map_height < 3)
		error_print_exit(ERR_MAP_HEIGHT, game);
	return (0);
}
