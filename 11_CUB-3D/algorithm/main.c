/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/26 21:54:40 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

/**
 * @brief Keeps an angle in the range [0, 2*PI].
 *
 * If the angle is less than 0, it adds 2*PI to shift it to the [0, 2*PI] range.
 * If the angle is more than 2*PI, it subtracts 2*PI to shift it
 * to the [0, 2*PI] range = 360 degrees = [0, 6.283185] range.
 */
static double	keep_in_range(double angle)
{
	if (angle < 0)
		angle += 2 * PI_FT;
	else if (angle > 2 * PI_FT)
		angle -= 2 * PI_FT;
	return (angle);
}

static double	distance(t_player *player, double x, double y)
{
	return (sqrt(pow(x - player->pos.x, 2) + pow(y - player->pos.y, 2)));
}

static int	wall_hit(t_map *map, double x, double y)
{
	int	m_x;
	int	m_y;

	if (x < 0 || y < 0)
		return (0);
	m_x = floor (x / TILE_SIZE);
	m_y = floor (y / TILE_SIZE);
	if (m_y >= map->height || m_y < 0 || m_x >= map->width || m_x < 0)
		return (0);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (0);
	return (1);
}

static void	find_hit(t_main *game, double x, double y, double x_step,
						double y_step, int pixel, int orientation)
{
	if (orientation == 'V')
	{
		while (wall_hit(game->file->map, x - pixel, y))
		{
			x += x_step;
			y += y_step;
		}
	}
	if (orientation == 'H')
	{
		while (wall_hit(game->file->map, x, y - pixel))
		{
			x += x_step;
			y += y_step;
		}
	}
	if (game->ray->distance < distance(game->player, x, y))
	{
		game->ray->hit.x = x;
		game->ray->hit.y = y;
		game->ray->distance = distance(game->player, x, y);
	}
}

static void	calculate_vertical_hit(t_main *game, t_player *player, t_ray *ray)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	bool	facing_north;
	bool	facing_west;
	int		pixel;

	facing_north = ray->angle > 0 && ray->angle < PI_FT;
	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;

	y_step = facing_north ? TILE_SIZE : -TILE_SIZE;
	x_step = TILE_SIZE / tan(ray->angle);
	if ((facing_west && x_step > 0) || (!facing_west && x_step < 0))
		x_step *= -1;

	y_intercept = floor(player->pos.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += facing_north ? TILE_SIZE : 0;
	x_intercept = player->pos.x + (y_intercept - player->pos.y) / tan(ray->angle);

	pixel = facing_north ? -1 : 1;
	find_hit(game, x_intercept, y_intercept, x_step, y_step, pixel, 'V');
}

static void	calculate_horizontal_hit(t_main *game, t_player *player, t_ray *ray)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	bool	facing_west;
	bool	facing_north;
	int		pixel;

	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;
	facing_north = ray->angle > 0 && ray->angle < PI_FT;

	x_step = facing_west ? -TILE_SIZE : TILE_SIZE;
	y_step = TILE_SIZE * tan(ray->angle);
	if ((facing_north && y_step < 0) || (!facing_north && y_step > 0))
		y_step *= -1;

	x_intercept = floor(player->pos.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += facing_west ? 0 : TILE_SIZE;
	y_intercept = player->pos.y + (x_intercept - player->pos.x) * tan(ray->angle);

	pixel = facing_west ? 1 : -1;
	find_hit(game, x_intercept, y_intercept, x_step, y_step, pixel, 'H');
}

/**
 * @brief Casts rays from the player's position in 3D.
 *
 * It first sets the initial ray angle to the player's angle minus half
 * of the field of view.
 * 
 * Then, for each column of the screen, it normalizes the ray angle,
 * calculates the vertical and horizontal intersections of the ray with a wall,
 * and selects the shortest ray. It then draws the 3D projection of the wall
 * on the screen.
 * 
 * Finally, it increments the ray angle by the field of view divided
 * by the screen width and repeats the process for the next column.
 */
static void	ray_cast(t_main *game, t_player *player, t_ray *ray)
{
	int		ray_counter;
	double	raw_ray_angle;

	raw_ray_angle = player->dir.rad - (player->fov.rad / 2);
	ray_counter = -1;
	game->ac = 3;	// delete
	while (++ray_counter < SWIDTH)
	{
		ray->angle = keep_in_range(raw_ray_angle);
		calculate_vertical_hit(game, player, ray);
		calculate_horizontal_hit(game, player, ray);
		// pick_shortest_ray(ray);
		if (ray_counter % 100 == 0)
		{
			printf("hit ray dist: %f   x: %f   y: %f\n", ray->distance, ray->hit.x, ray->hit.y);
			printf("*****************************\n");
		}
		// draw_ray(game, ray_counter, raw_ray_angle);
		raw_ray_angle += (player->fov.rad / SWIDTH);
	}
}

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

static void	put_image(t_main *game)
{
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, (uint32_t)SWIDTH, (uint32_t)SHEIGHT);
	ray_cast(game, game->player, game->ray);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

static void	game_loop(void *param)
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
	ft_debug(MAP, game);	// delete
	put_image(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
