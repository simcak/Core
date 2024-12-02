/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:54:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 19:56:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static bool	ft_isspace(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

static bool	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

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
