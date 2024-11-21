/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:20:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/21 14:58:27 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Finds the index of the last non-space character in the input string.
 *
 * @return The index of the last non-space character, or -1 if no non-space
 * character is found.
 */
int	last_char_index(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && is_space(str[i]))
		i--;
	if (i < 0)
		return (0);
	return (i);
}
