/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:33:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/06 18:13:54 by psimcak          ###   ########.fr       */
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

int	free_map(t_map *map)
{
	if (map->parsed_file)
		free_str_arr(map->parsed_file);
	if (map->txt_paths)
		free_str_arr(map->txt_paths);
	if (map->mlx_txt_no)
		mlx_delete_texture(map->mlx_txt_no);
	if (map->mlx_txt_so)
		mlx_delete_texture(map->mlx_txt_so);
	if (map->mlx_txt_we)
		mlx_delete_texture(map->mlx_txt_we);
	if (map->mlx_txt_ea)
		mlx_delete_texture(map->mlx_txt_ea);
	free(map);
	return (EXIT_SUCCESS);
}

int	free_parser(t_main *game)
{
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
	return (EXIT_SUCCESS);
}

void	free_full(t_main *game)
{
	if (game->map)
		free_map(game->map);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->mlx)
	{
		mlx_delete_image(game->mlx, game->image);
		mlx_delete_image(game->mlx, game->animation);
		mlx_delete_texture(game->animation_txt);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (game)
		free(game);
}
