/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/24 15:02:31 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_default_player(t_main *game)
{
	game->player = ft_smalloc(sizeof(t_player), ERR_MALL"PLAYER"RST);

	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->cam_x = 0;
	game->player->cam_y = 0;
	game->player->move_speed = 0;
	game->player->rot_speed = 0;
	game->player->buff_dist = 0;
	game->player->aspect_ratio = 0;
	game->player->step_x = 0;
	game->player->step_y = 0;
}

static void	init_default_ray(t_main *game)
{
	game->ray = ft_smalloc(sizeof(t_ray), ERR_MALL"RAY"RST);

	game->ray->angle = 0;
	game->ray->distance = 0;
}

static void	init_default_file(t_main *game)
{
	game->file = ft_smalloc(sizeof(t_file), ERR_MALL"FILE"RST);

	game->file->fd = 0;
	game->file->parsed_file = NULL;
}

static void	init_default_txt(t_file *file)
{
	file->txt = ft_smalloc(sizeof(t_txt), ERR_MALL"TXT"RST);

	file->txt->paths = NULL;
	file->txt->mlx_txt_no = NULL;
	file->txt->mlx_txt_so = NULL;
	file->txt->mlx_txt_we = NULL;
	file->txt->mlx_txt_ea = NULL;
}

static void	init_default_color(t_file *file)
{
	file->color = ft_smalloc(sizeof(t_color), ERR_MALL"COLOR"RST);

	file->color->colors = NULL;
	file->color->rgb_raw = NULL;
	file->color->rgb_c = NULL;
	file->color->rgb_f = NULL;
}

static void init_default_map(t_file *file)
{
	file->map = ft_smalloc(sizeof(t_map), ERR_MALL"MAP"RST);

	file->map->grid = NULL;
	file->map->width = 0;
	file->map->height = 0;
	file->map->start_pos.x = -1;
	file->map->start_pos.y = -1;
	file->map->start_pos.nswe = '\0';
}

/**
 * @brief Checks the arguments validity.
 * 
 * 1) Checks the number of arguments.
 * 2) Checks the file extension.
 * 3) Checks the file descriptor.
 * 
 * If there is some problem, the program exits with an error message.
 */
static void	argument_checker(t_main *game)
{
	int		len;

	if (game->ac != 2)
		safe_exit(game, BR"Input has to be: \"./cub3d <map.cub>\""RST);
	len = ft_strlen(game->av[1]);
	if (ft_strncmp(&game->av[1][len - 4], ".cub", 4) != 0)
		safe_exit(game, BR"Input file has to be \".cub\""RST);
	game->file->fd = open(game->av[1], O_RDONLY);
	if (game->file->fd < 0)
		safe_exit(game, BR"Invalid file"RST);
}

/**
 * @brief Initialize default game struct
 */
void	init_default(t_main *game)
{
	game->mlx = NULL;
	game->image = NULL;
	init_default_player(game);
	init_default_ray(game);
	init_default_file(game);
	init_default_txt(game->file);
	init_default_color(game->file);
	init_default_map(game->file);
	argument_checker(game);
}