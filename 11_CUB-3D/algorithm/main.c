/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 19:56:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static void	put_image(t_main *game)
{
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, (uint32_t)SWIDTH, (uint32_t)SHEIGHT);
	ray_cast(game, game->player, game->ray);
	put_mini_map(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

static void	game_loop(void *param)
{
	t_main	*game;
	bool	pressed;

	game = (t_main *)param;
	pressed = key_down_crossroad(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (pressed)
		put_image(game);
}

/**
 * @brief Main function
 * 
 * 1) INITIALIZATION / PARSING
 * 1.1) Initialize all structures w/ default values + check the args validity
 * 1.2) for file = PARSING
 * 1.3) assign specific values to the player struct
 * 1.4) initialize mlx = heat up graphics
 * 2) LOOP / RAYCASTING
 * 2.1) 
 *
 * ) mlx loop keeps the window open - just like while loop
 */
int	main(int ac, char **av)
{
	t_main	*game;

	game = ft_smalloc(sizeof(t_main), BR""ERR_MALL"GAME"RST);
	game->ac = ac;
	game->av = av;
	init(DEFAULT, game);
	init(FILE, game);
	init(PLAYER, game);
	init(MLX, game);
	put_image(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
