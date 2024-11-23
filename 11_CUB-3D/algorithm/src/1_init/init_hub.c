/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 17:19:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#define LP	"/Users/psimcak/Documents/Core/11_CUB-3D/maps/textures/logo.png"

// static bool	init_animation(t_main *game)
// {
// 	game->animation_txt = mlx_load_png(LP);
// 	if (!(game->animation_txt))
// 	{
// 		mlx_close_window(game->mlx);
// 		perror(mlx_strerror(mlx_errno));
// 		safe_exit(game, mlx_strerror(mlx_errno));
// 		return (false);
// 	}
// 	game->animation = mlx_texture_to_image(game->mlx, game->animation_txt);
// 	if (!(game->animation))
// 	{
// 		mlx_close_window(game->mlx);
// 		perror(mlx_strerror(mlx_errno));
// 		safe_exit(game, mlx_strerror(mlx_errno));
// 		return (false);
// 	}
// 	return (true);
// }

// static bool	init_mlx42(t_main *game)
// {
// 	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", 0);
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

/**
 * @brief Checks the arguments validity.
 * 
 * 1) Checks the number of arguments.
 * 2) Checks the file extension.
 * 3) Checks the file descriptor.
 * 
 * If there is some problem, the program exits with an error message.
 */
static void	argument_checker(int ac, char **av, t_main *game)
{
	int	len;

	if (ac != 2)
		safe_exit(game, BR"Input has to be: \"./cub3d <map.cub>\""RST);
	len = ft_strlen(av[1]);
	if (ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
		safe_exit(game, BR"Input file has to be \".cub\""RST);
	game->file->fd = open(av[1], O_RDONLY);
	if (game->file->fd < 0)
		safe_exit(game, BR"Invalid file"RST);
}

static void	init_player(t_main *game, t_map *map)
{
	if (map->start_pos.nswe == 'E' || map->start_pos.nswe == 'W')
	{
		game->player->dir_x = (map->start_pos.nswe == 'E') ? 1 : -1;
		game->player->dir_y = 0;
		game->player->cam_x = 0;
		game->player->cam_y = (map->start_pos.nswe == 'E') ? 0.5 : -0.5;
	}
	if (map->start_pos.nswe == 'N' || map->start_pos.nswe == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = (map->start_pos.nswe == 'S') ? 1 : -1;
		game->player->cam_x = (map->start_pos.nswe == 'S') ? 0.5 : -0.5;
		game->player->cam_y = 0;
	}
	game->player->pos_x = map->start_pos.x + 0.5;
	game->player->pos_y = map->start_pos.y + 0.5;
}

/**
 * @brief Initializes the game structure with default values.
 */
void	init(int type, t_main *game, int ac, char **av)
{
	if (type == DEFAULT)
	{
		init_default(game);
		argument_checker(ac, av, game);
	}
	else if (type == PLAYER)
		init_player(game, game->map);
	else
		safe_exit(game, BR"Invalid type"RST);
}
