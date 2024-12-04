/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:32:36 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/04 15:13:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Every time we want to exit the program we first free all memory.
 * 
 * By the subject we have to write "Error\n" before the message.
 */
void	safe_exit(t_main *game, const char *msg)
{
	write(2, "Error\n", 6);
	printf("%s\n", msg);
	if (game)
		free_full(game);
	exit(EXIT_FAILURE);
}
