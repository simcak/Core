/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:32:36 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/02 15:53:30 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	safe_exit(t_main *game, const char *msg)
{
	safe_free(game);
	perror(msg);
	exit(EXIT_FAILURE);
}
