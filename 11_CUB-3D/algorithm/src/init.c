/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/29 20:52:23 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// static bool	init_animation(t_game *game)
// {
// 	game->animation_txt = mlx_load_png("../../maps/textures/logo.png");
// 	if (!(game->animation_txt))
// 	{
// 		mlx_close_window(game->mlx);
// 		perror(mlx_strerror(mlx_errno));
// 		// safe_exit(game, mlx_strerror(mlx_errno));
// 		return (false);
// 	}
// 	game->animation = mlx_texture_to_image(game->mlx, game->animation_txt);
// 	if (!(game->animation))
// 	{
// 		mlx_close_window(game->mlx);
// 		perror(mlx_strerror(mlx_errno));
// 		// safe_exit(game, mlx_strerror(mlx_errno));
// 		return (false);
// 	}
// 	return (true);
// }

// static bool	init_mlx42(t_game *game)
// {
// 	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", 0);
// 	if (!game->mlx)
// 		return (false);
// 	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1 ||
// 		!(game->image))
// 	{
// 		mlx_close_window(game->mlx);
// 		return (false);
// 	}
// 	init_animation(game);
// 	return (true);
// }

static void init_empty_map(t_game *game)
{
	game->map = ft_safe_malloc(sizeof(t_map), ERR_MALL_MAP);
	game->map->fd = 0;
	game->map->parsed_file = NULL;
	game->map->grid = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->start_count = 0;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->start_dir = '\0';
	game->map->txt_no = NULL;
	game->map->txt_so = NULL;
	game->map->txt_we = NULL;
	game->map->txt_ea = NULL;
	game->map->mlx_txt_no = NULL;
	game->map->mlx_txt_so = NULL;
	game->map->mlx_txt_we = NULL;
	game->map->mlx_txt_ea = NULL;
}

static void	init_empty(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->animation = NULL;
	game->animation_txt = NULL;
	game->player = NULL;
	game->ray = NULL;
	init_empty_map(game);
}

void	init(int type, t_game *game)
{
	if (type == EMPTY)
		init_empty(game);
	// else if (type == GAME)
	// 	init_game_struct(game);
	// else if(type == MLX)
	// 	init_mlx42(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
