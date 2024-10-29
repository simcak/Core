/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:51 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/29 21:01:12 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3D.h"

int	main(void)
{
	t_game	*game;

	game = ft_safe_malloc(sizeof(t_game), ERR_MALL_GAME);
	init(EMPTY, game);
	init(MLX, game);
	safe_free(game);
	return (EXIT_SUCCESS);
}
