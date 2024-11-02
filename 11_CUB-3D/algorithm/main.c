/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/02 16:31:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	main(int ac, char **av)
{
	t_main	*game;

	game = ft_safe_malloc(sizeof(t_main), ERR_MALL_GAME);
	init(DEFAULT, game, ac, av);
	// ft_debug(ALL, game);
	// init(MLX, game, 0, NULL);
	safe_free(game);
	return (EXIT_SUCCESS);
}
