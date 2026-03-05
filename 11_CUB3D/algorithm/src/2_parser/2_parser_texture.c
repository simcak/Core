/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_texture_zp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:39 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:59:57 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Checks if there is ONE flag in the parsed file.
 * If so, it returns the path to the texture - just characters after the flag.
 * If not, it exits the program.
 */
static void	ft_safe_texture(char *flag, t_main *game, int i)
{
	int		line;
	int		flag_count;
	t_txt	*txt;

	line = -1;
	flag_count = 0;
	txt = game->file->txt;
	while (game->file->parsed_file[++line])
	{
		if (we_found_flag(game, flag, line))
		{
			flag_count++;
			txt->paths[i] = txt_path_finder(game, (int)ft_strlen(flag), line);
		}
	}
	if (flag_count < 1)
		safe_exit(game, BR"Missing texture flag in the parsed file"RST);
	else if (flag_count > 1)
		safe_exit(game, BR"Duplicate texture flag in the parsed file"RST);
}

/**
 * @brief Checks if there are any duplications or empty values in parsed file.
 * CALLER: parse_load_check_texture
 */
static void	ft_dupliempty_txtp(t_main *game, char **txt_paths)
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
				safe_exit(game, BR"Empty value in the texture path"RST);
			if (ft_strncmp(txt_paths[i], txt_paths[j],
					ft_strlen(txt_paths[i])) == 0)
				safe_exit(game, BR"Duplicate value of the txt path"RST);
		}
	}
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
	bool	mlx_txt_loaded;

	txt->paths = ft_smalloc(sizeof(char *) * 5, BR""ERR_MALL_2D"TEXTURE"RST);
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
	mlx_txt_loaded = txt->mlx_txt_no && txt->mlx_txt_so && txt->mlx_txt_we
		&& txt->mlx_txt_ea;
	if (!mlx_txt_loaded)
		safe_exit(game, BR"Failed to load mlx textures"RST);
}
