/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/27 00:55:20 by psimcak          ###   ########.fr       */
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
	angle = angle < 0 ? angle + 2 * PI_FT : angle;
	angle = angle > 2 * PI_FT ? angle - 2 * PI_FT : angle;
	return (angle);
}

/**
 * @brief Calculates the distance between two points.
 * 
 * formula: sqrt((rx - px)^2 + (ry - py)^2)
 * 
 * @param px - player's x coordinate
 * @param py - player's y coordinate
 * @param rx - ray's x coordinate
 * @param ry - ray's y coordinate
 */
static double	distance(double px, double py, double rx, double ry)
{
	return (sqrt(pow(rx - px, 2) + pow(ry - py, 2)));
}

static void	pick_shorter_ray(t_player *p, t_ray *ray)
{
	double	v_distance;
	double	h_distance;

	v_distance = distance(p->pos.x, p->pos.y, ray->vhit.x, ray->vhit.y);
	h_distance = distance(p->pos.x, p->pos.y, ray->hhit.x, ray->hhit.y);
	if (h_distance < v_distance)
	{
		ray->distance = h_distance;
		ray->hit.x = ray->hhit.x;
		ray->hit.y = ray->hhit.y;
	}
	else
	{
		ray->distance = v_distance;
		ray->hit.x = ray->vhit.x;
		ray->hit.y = ray->vhit.y;
	}
}

static int	wall_not_hit(t_map *map, double ray_hit_x, double ray_hit_y)
{
	int	m_x;
	int	m_y;

	if (ray_hit_x < 0 || ray_hit_y < 0)
		return (0);
	m_x = floor(ray_hit_x / TILE_SIZE);
	m_y = floor(ray_hit_y / TILE_SIZE);
	if (m_y >= map->height || m_y < 0 || m_x >= map->width || m_x < 0)
		return (0);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (0);
	return (1);
}

static void	calculate_vertical_hit(t_main *game, t_player *player, t_ray *ray)
{
	bool	facing_north;
	bool	facing_west;
	int		pixel;

	facing_north = ray->angle > 0 && ray->angle < PI_FT;
	facing_west = ray->angle > PI_FT / 2 && ray->angle < 3 * PI05_FT;

	ray->y_step = facing_north ? TILE_SIZE : -TILE_SIZE;
	ray->x_step = TILE_SIZE / tan(ray->angle);
	if ((facing_west && ray->x_step > 0) || (!facing_west && ray->x_step < 0))
		ray->x_step *= -1;

	ray->vhit.y = floor(player->pos.y / TILE_SIZE) * TILE_SIZE;
	ray->vhit.y += facing_north ? TILE_SIZE : 0;
	ray->vhit.x = player->pos.x + (ray->vhit.y - player->pos.y) / tan(ray->angle);

	pixel = facing_north ? -1 : 1;
	while (wall_not_hit(game->file->map, ray->vhit.x, ray->vhit.y - pixel))
	{
		ray->vhit.x += ray->x_step;
		ray->vhit.y += ray->y_step;
	}
}

static void	calculate_horizontal_hit(t_main *game, t_player *player, t_ray *ray)
{
	bool	facing_west;
	bool	facing_north;
	int		pixel;

	facing_west = ray->angle > PI05_FT && ray->angle < 3 * PI05_FT;
	facing_north = ray->angle > 0 && ray->angle < PI_FT;

	ray->x_step = facing_west ? -TILE_SIZE : TILE_SIZE;
	ray->y_step = TILE_SIZE * tan(ray->angle);
	if ((facing_north && ray->y_step < 0) || (!facing_north && ray->y_step > 0))
		ray->y_step *= -1;

	ray->hhit.x = floor(player->pos.x / TILE_SIZE) * TILE_SIZE;
	ray->hhit.x += facing_west ? 0 : TILE_SIZE;
	ray->hhit.y = player->pos.y + (ray->hhit.x - player->pos.x) * tan(ray->angle);

	pixel = facing_west ? 1 : -1;
	while (wall_not_hit(game->file->map, ray->hhit.x - pixel, ray->hhit.y))
	{
		ray->hhit.x += ray->x_step;
		ray->hhit.y += ray->y_step;
	}
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

	ray_counter = -1;
	raw_ray_angle = player->dir.rad - (player->fov_rad / 2);
	while (++ray_counter < SWIDTH)
	{
		ray->angle = keep_in_range(raw_ray_angle);
		calculate_vertical_hit(game, player, ray);
		calculate_horizontal_hit(game, player, ray);
		pick_shorter_ray(player, ray);
		// draw_ray(game, ray_counter, raw_ray_angle);
		raw_ray_angle += player->fov_rad / SWIDTH;
	}
	exit(0);	// TEMPORARY
}

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
