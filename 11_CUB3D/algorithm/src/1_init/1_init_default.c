/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:59:37 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_default_ray(t_main *game)
{
	game->ray = ft_smalloc(sizeof(t_ray), BR""ERR_MALL"RAY"RST);
	game->ray->orientation = 0;
	game->ray->pixel = 0;
	game->ray->angle = 0;
	game->ray->angle_diff = 0;
	game->ray->distance = 0;
	game->ray->x_step = 0;
	game->ray->y_step = 0;
	game->ray->color = 0;
	game->ray->hhit.x = 0;
	game->ray->hhit.y = 0;
	game->ray->vhit.x = 0;
	game->ray->vhit.y = 0;
	game->ray->hit.x = 0;
	game->ray->hit.y = 0;
}

static void	init_default_wall(t_main *game)
{
	game->wall = ft_smalloc(sizeof(t_wall), BR""ERR_MALL"WALL"RST);
	game->wall->height = 0;
	game->wall->start = 0;
	game->wall->end = 0;
	game->wall->clr = NULL;
	game->wall->txt = NULL;
}

static void	init_def_file(t_main *game)
{
	game->file = ft_smalloc(sizeof(t_file), BR""ERR_MALL"FILE"RST);
	game->file->fd = 0;
	game->file->parsed_file = NULL;
	game->file->txt = ft_smalloc(sizeof(t_txt), BR""ERR_MALL"TXT"RST);
	game->file->txt->paths = NULL;
	game->file->txt->mlx_txt_no = NULL;
	game->file->txt->mlx_txt_so = NULL;
	game->file->txt->mlx_txt_we = NULL;
	game->file->txt->mlx_txt_ea = NULL;
	game->file->color = ft_smalloc(sizeof(t_color), BR""ERR_MALL"COLOR"RST);
	game->file->color->colors = NULL;
	game->file->color->rgb_raw = NULL;
	game->file->color->rgb_c = NULL;
	game->file->color->rgb_f = NULL;
	game->file->color->c_color = 0;
	game->file->color->f_color = 0;
	game->file->map = ft_smalloc(sizeof(t_map), BR""ERR_MALL"MAP"RST);
	game->file->map->grid = NULL;
	game->file->map->grid_max = NULL;
	game->file->map->width = 0;
	game->file->map->height = 0;
	game->file->map->start_pos.x = -1;
	game->file->map->start_pos.y = -1;
	game->file->map->start_pos.nswe = '\0';
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
	game->player = ft_smalloc(sizeof(t_player), BR""ERR_MALL"PLAYER"RST);
	init_default_ray(game);
	init_default_wall(game);
	init_def_file(game);
	argument_checker(game);
}
