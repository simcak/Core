/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:54:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/02 15:42:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * If there is an error in malloc, print the error message and exit the program
 * We are allowed to use malloc, perror and exit (also strerror)
 */
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
