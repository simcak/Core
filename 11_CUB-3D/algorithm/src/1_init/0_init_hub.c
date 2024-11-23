/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 19:59:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

static void	init_mlx42(t_main *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	if (!game->mlx)
		safe_exit(game, mlx_strerror(mlx_errno));
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(game->image))
		safe_exit(game, mlx_strerror(mlx_errno));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		safe_exit(game, mlx_strerror(mlx_errno));
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
	else if (type == FILE)
		parser(game);
	else if (type == PLAYER)
		init_player(game, game->file->map);
	else if (type == MLX)
		init_mlx42(game);
	else
		safe_exit(game, BR"Invalid type"RST);
}
