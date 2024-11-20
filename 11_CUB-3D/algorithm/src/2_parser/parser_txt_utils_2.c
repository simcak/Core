/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/07 18:25:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Checks if there are any duplications or empty values in parsed file.
 * CALLER: parse_load_check_texture
 */
void	ft_dupliempty_txtp(t_main *game, char **txt_paths)
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
