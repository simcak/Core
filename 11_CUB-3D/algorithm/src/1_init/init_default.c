/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 17:43:39 by psimcak          ###   ########.fr       */
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

static void	init_default_txt(t_main *game)
{
	game->txt = ft_smalloc(sizeof(t_txt), ERR_MALL"TXT"RST);

	game->txt->paths = NULL;
	game->txt->mlx_txt_no = NULL;
	game->txt->mlx_txt_so = NULL;
	game->txt->mlx_txt_we = NULL;
	game->txt->mlx_txt_ea = NULL;
}

static void	init_default_color(t_main *game)
{
	game->color = ft_smalloc(sizeof(t_color), ERR_MALL"COLOR"RST);

	game->color->colors = NULL;
	game->color->rgb_raw = NULL;
	game->color->rgb_c = NULL;
	game->color->rgb_f = NULL;
}

static void init_default_map(t_main *game)
{
	game->map = ft_smalloc(sizeof(t_map), ERR_MALL"MAP"RST);

	game->map->grid = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->start_pos.x = -1;
	game->map->start_pos.y = -1;
	game->map->start_pos.nswe = '\0';
}

/**
 * @brief Initialize default game struct
 */
void	init_default(t_main *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->animation = NULL;
	game->animation_txt = NULL;
	init_default_player(game);
	init_default_ray(game);
	init_default_file(game);
	init_default_txt(game);
	init_default_color(game);
	init_default_map(game);
}
