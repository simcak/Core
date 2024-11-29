/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:33:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/29 19:49:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	free_str_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (EXIT_SUCCESS);
}

static void	free_mlx(t_main *game)
{
	if (game->mlx)
	{
		if (game->image)
			mlx_delete_image(game->mlx, game->image);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	return ;
}

static void	free_txt(t_txt *txt)
{
	if (txt)
	{
		if (txt->paths)
			free(txt->paths);
		if (txt->mlx_txt_no)
			mlx_delete_texture(txt->mlx_txt_no);
		if (txt->mlx_txt_so)
			mlx_delete_texture(txt->mlx_txt_so);
		if (txt->mlx_txt_we)
			mlx_delete_texture(txt->mlx_txt_we);
		if (txt->mlx_txt_ea)
			mlx_delete_texture(txt->mlx_txt_ea);
		free(txt);
	}
	return ;
}

static void	free_color(t_color *color)
{
	if (color)
	{
		if (color->colors)
			free(color->colors);
		if (color->rgb_raw)
			free_str_arr(color->rgb_raw);
		if (color->rgb_c)
			free(color->rgb_c);
		if (color->rgb_f)
			free(color->rgb_f);
		free(color);
	}
	return ;
}

/**
 * txt_paths is a 2D array of POINTERS to the parsed file. Therefore, we don't
 * need 2D free function.
 * same goes for colors
 */
void	free_full(t_main *game)
{
	free_mlx(game);
	free_txt(game->file->txt);
	free_color(game->file->color);
	if (game->file->map)
	{
		if (game->file->map->grid)
			free_str_arr(game->file->map->grid);
		if (game->file->map->grid_max)
			free_str_arr(game->file->map->grid_max);
		free(game->file->map);
	}
	if (game->file)
	{
		if (game->file->parsed_file)
			free_str_arr(game->file->parsed_file);
		free(game->file);
	}
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->wall)
		free(game->wall);
	if (game)
		free(game);
}
