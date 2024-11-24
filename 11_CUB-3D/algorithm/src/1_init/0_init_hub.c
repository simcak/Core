/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 14:57:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_mlx42(t_main *game)
{
	game->mlx = mlx_init(SWIDTH, SHEIGHT, "cub3D", false);
	if (!game->mlx)
		safe_exit(game, mlx_strerror(mlx_errno));
	game->image = mlx_new_image(game->mlx, SWIDTH, SHEIGHT);
	if (!(game->image))
		safe_exit(game, mlx_strerror(mlx_errno));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		safe_exit(game, mlx_strerror(mlx_errno));
}

/**
 * @brief Initializes the game structure with default values.
 */
void	init(int type, t_main *game)
{
	if (type == DEFAULT)
		init_default(game);
	else if (type == FILE)
		parser(game);
	else if (type == PLAYER)
		init_player(game->player, game->file->map);
	else if (type == MLX)
		init_mlx42(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
