/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/20 21:54:42 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"
# define ERR_MALL_GAME	BR"Memory allocation failed for game"RST

int	main(int ac, char **av)
{
	t_main	*game;

	game = ft_smalloc(sizeof(t_main), ERR_MALL_GAME);
	init(DEFAULT, game, ac, av);
	parser(game);
	// init(MLX, game, 0, NULL);	// TODO
	ft_debug(ALL, game);
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
