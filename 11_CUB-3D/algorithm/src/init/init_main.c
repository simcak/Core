/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/31 20:31:47 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#define LP	"/Users/psimcak/Documents/Core/11_CUB-3D/maps/textures/logo.png"

static bool	init_animation(t_game *game)
{
	game->animation_txt = mlx_load_png(LP);
	if (!(game->animation_txt))
	{
		mlx_close_window(game->mlx);
		perror(mlx_strerror(mlx_errno));
		safe_exit(game, mlx_strerror(mlx_errno));
		return (false);
	}
	game->animation = mlx_texture_to_image(game->mlx, game->animation_txt);
	if (!(game->animation))
	{
		mlx_close_window(game->mlx);
		perror(mlx_strerror(mlx_errno));
		safe_exit(game, mlx_strerror(mlx_errno));
		return (false);
	}
	return (true);
}

static bool	init_mlx42(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", 0);
	if (!game->mlx)
		return (false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1 ||
		!(game->image))
	{
		mlx_close_window(game->mlx);
		return (false);
	}
	init_animation(game);
	return (true);
}

void	init(int type, t_game *game)
{
	if (type == EMPTY)
		init_empty(game);
	// else if (type == GAME)
	// 	init_game_struct(game);
	else if(type == MLX)
		init_mlx42(game);
	// else if (type == ANIMATION)
	// 	init_animation(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
