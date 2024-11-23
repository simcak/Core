/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/23 18:11:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	main(int ac, char **av)
{
	t_main	*game;

	game = ft_smalloc(sizeof(t_main), ERR_MALL"GAME"RST);
	init(DEFAULT, game, ac, av);
	init(FILE, game, 0, NULL);
	init(PLAYER, game, 0, NULL);
	ft_debug(ALL, game);	// delete
	free_full(game);
	// printf("Press RETURN to exit...\n");	// delete
	// getchar();			// delete
	return (EXIT_SUCCESS);
}
