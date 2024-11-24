/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 20:52:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

// void	ray_cast(t_main *game)
// {
// 	int	ray_counter;

// 	game->ray->angle = game->player->angle_rad - (game->player->fov_rad / 2);
// 	ray_counter = -1;
// 	while (++ray_counter < SWIDTH)
// 	{
// 		ray->angle_nor = normalize_angle(ray->r_a);
// 		calculate_vertical_hit(game->map, player, ray);
// 		calculate_horizontal_hit(game->map, player, ray);
// 		pick_shortest_ray(ray);
// 		project_ray_into_3d(game, ray_counter);
// 		ray->r_a += (player->fov_rd / WIDTH);
// 	}
// }

// void	ray_cast(t_main *game)
// {
// 	int		wall_height;
// 	int		ray_counter;

// 	ray_counter = -1;
// 	while (++ray_counter < SWIDTH)
// 	{
// 		calculate_cam(game, ray_counter);
// 		calculate_delta(game);
// 		calculate_pos(game);
// 		calculate_hit(game, false);
// 		calculate_ray(game, game->ray);
// 		wall_height = (int)(SWIDTH / game->ray->distance);
// 		draw_ceiling(game, ray_counter, draw_start(wall_height));
// 		draw_walls(game, ray_counter, draw_end(wall_height), wall_height);
// 		draw_floor(game, ray_counter, draw_end(wall_height));
// 	}
// }

void	put_image(t_main *game)
{
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, (uint32_t)SWIDTH, (uint32_t)SHEIGHT);
	// ray_cast(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

void	game_loop(void *param)
{
	t_main	*game;
	bool	pressed;

	game = (t_main *)param;
	pressed = false;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	// 	pressed = rot_left(game, game->player->rot_speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	// 	pressed = rot_right(game, game->player->rot_speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	// 	pressed = mov_forward(game, game->player->move_speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	// 	pressed = mov_back(game, game->player->move_speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	// 	pressed = mov_left(game, game->player->move_speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	// 	pressed = mov_right(game, game->player->move_speed);
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

	game = ft_smalloc(sizeof(t_main), ERR_MALL"GAME"RST);
	game->ac = ac;
	game->av = av;
	init(DEFAULT, game);
	init(FILE, game);
	init(PLAYER, game);
	init(MLX, game);
	ft_debug(ALL, game);	// delete
	put_image(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
