/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 10:15:56 by psimcak          ###   ########.fr       */
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
void	argument_checker(int ac, char **av, t_main *game)
{
	int	len;

	if (ac != 2)
		safe_exit(game, BR"Invalid number of arguments"RST);
	len = ft_strlen(av[1]);
	if (ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
		safe_exit(game, BR"Invalid file extension"RST);
	game->map->fd = open(av[1], O_RDONLY);
	if (game->map->fd < 0)
		safe_exit(game, BR"Invalid file"RST);
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
	// else if (type == GAME)
	// 	init_game_struct(game);
	// else if(type == MLX)
	// 	init_mlx42(game);
	// else if (type == ANIMATION)
	// 	init_animation(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
