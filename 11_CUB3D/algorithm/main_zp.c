/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_zp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 17:03:15 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	cursor_hook(double xpos, double ypos, void *param)
// {
// 	t_main	*game;

// 	game = (t_main *)param;
// 	game->player->dir.rad += ((xpos - SWIDTH / 2) * ROTATION_SPEED)
//			* (M_PI / 180);
// 	game->player->dir.rad = keep_in_range(game->player->dir.rad);
// 	mlx_set_mouse_pos(game->mlx, SWIDTH / 2, SHEIGHT / 2);
// 	(void)ypos;
// }

static void	put_image(t_main *game)
{
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, (uint32_t)SWIDTH, (uint32_t)SHEIGHT);
	ray_cast(game, game->player, game->ray);
	put_mini_map(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

/**
 * @brief Game loop
 * 
 * BONIUS: remove the pressed condition
 */
static void	game_loop(void *param)
{
	t_main	*game;
	bool	pressed;

	game = (t_main *)param;
	pressed = key_down_crossroad(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
	}
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
 * 1.5) put_image on the screen - no key pressed so we wouldn't see anything
 * 2) LOOP / RAYCASTING
 * 2.1) Ray is like a column of pixels and we draw it one by one BUT just when
 *      we press any action key
 * 2.2) with mlx_loop we keep the window open
 * 3) CLEANUP
 * ) mlx loop keeps the window open - just like while loop
 * 
 * BONUS:
 * mlx_cursor_hook(game->mlx, &cursor_hook, game);
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
	return (EXIT_SUCCESS);
}
