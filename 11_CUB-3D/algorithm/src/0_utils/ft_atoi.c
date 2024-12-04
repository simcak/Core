/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:54:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/04 15:10:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Converts the initial string of characters to an integer.
 * 
 * Covers spaces before and one sign after the spaces. Than it goes till the
 * first non-digit character and returns the result.
 */
int	ft_atoi(const char *original_str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(original_str[i]))
		i++;
	if (original_str[i] == '-' || original_str[i] == '+')
	{
		if (original_str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(original_str[i]))
	{
		result = result * 10 + (original_str[i] - '0');
		i++;
	}
	return (result * sign);
}
