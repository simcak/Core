/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:32:36 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/31 20:33:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	safe_exit(t_game *game, const char *msg)
{
	safe_free(game);
	perror(msg);
	exit(EXIT_FAILURE);
}
