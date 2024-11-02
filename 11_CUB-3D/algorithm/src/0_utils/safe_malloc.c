/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:54:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/02 15:36:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	*ft_safe_malloc(size_t size, char *msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
