/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:32:36 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/06 18:26:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_perror(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	safe_exit(t_main *game, const char *msg)
{
	write(2, "Error\n", 6);
	printf("%s\n", msg);
	if (game)
		free_parser(game);
	exit(EXIT_FAILURE);
}
