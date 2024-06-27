/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:24:25 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/27 16:22:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Those 2 functions are called "inline functions" and we use them for better
 * readebility.
 */
static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

/**
 * Convert string to long number
 */
long	ft_atol(char *argv_i)
{
	long	output_num;
	int		sign;
	int		i;

	output_num = 0;
	sign = 1;
	i = 0;
	while (argv_i[i] && is_space(argv_i[i]))
		i++;
	if (argv_i[i] == '+')
		i++;
	else if (argv_i[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (is_digit(argv_i[i]))
		output_num = (output_num * 10) + (argv_i[i++] - '0');
	return (output_num * sign);
}
