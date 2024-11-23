/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:39 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 18:04:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define ERR_MALL_TXT		BR"Malloc failed for 2D texture setup"RST

static bool	mlx_texture_loaded(t_txt *txt)
{
	return (txt->mlx_txt_no && txt->mlx_txt_so && txt->mlx_txt_we
		&& txt->mlx_txt_ea);
}

/**
 * Checks if there is ONE flag in the parsed file.
 * If so, it returns the path to the texture - just characters after the flag.
 * If not, it exits the program.
 */
void	ft_safe_texture(char *flag, t_main *game, int i)
{
	int		line;
	int		flag_count;

	line = -1;
	flag_count = 0;
	while (game->file->parsed_file[++line])
	{
		if (we_found_flag(game, flag, line))
		{
			flag_count++;
			game->file->txt->paths[i] = txt_path_finder(game, flag, line);
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing texture flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate texture flag in the parsed file"RST);
}

/**
 * TEXTURE RULES
 * - Except for the map content, each type of element can be separated by one or
    more empty line(s)
 * - Except for the map content which always has to be the last, each type of
    element can be set in any order in the file
 * - Except for the map, each type of information from an element can be
    separated by one or more space(s)
 * - You must be able to parse any kind of map, as long as it respects the rules
    of the map
 */
void	parse_load_check_texture(t_main *game, t_txt *txt)
{
	txt->paths = ft_dalloc(sizeof(char *), 5, ERR_MALL_TXT);
	ft_safe_texture("NO", game, 0);
	ft_safe_texture("SO", game, 1);
	ft_safe_texture("WE", game, 2);
	ft_safe_texture("EA", game, 3);
	txt->paths[4] = NULL;
	ft_dupliempty_txtp(game, txt->paths);

	txt->mlx_txt_no = mlx_load_png(txt->paths[0]);
	txt->mlx_txt_so = mlx_load_png(txt->paths[1]);
	txt->mlx_txt_we = mlx_load_png(txt->paths[2]);
	txt->mlx_txt_ea = mlx_load_png(txt->paths[3]);
	if (!mlx_texture_loaded(txt))
		safe_exit(game, BR"Failed to load mlx textures"RST);
}
