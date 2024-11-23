/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 19:59:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	game_loop(void *param)
{
	t_main	*game;

	game = (t_main *)param;
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		safe_exit(game, mlx_strerror(mlx_errno));
	}
	// cast_rays_3d(game, game->player, game->ray);
	// draw_2d_minimap(game, game->player);
	// play_animation(game);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		safe_exit(game, mlx_strerror(mlx_errno));
	}
}

int	main(int ac, char **av)
{
	t_main	*game;

	game = ft_smalloc(sizeof(t_main), ERR_MALL"GAME"RST);
	init(DEFAULT, game, ac, av);
	init(FILE, game, 0, NULL);
	init(PLAYER, game, 0, NULL);
	init(MLX, game, 0, NULL);
	mlx_loop_hook(game->mlx, &game_loop, game);
	ft_debug(ALL, game);	// delete
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
