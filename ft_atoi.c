/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:01:06 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/16 19:06:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	if (!str)
		return (0);
	while (str[i] < 33 && str[i] > 0)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i + 1] < '0' || str[i + 1] > '9')
		return (0);
	while (str[i])
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			number = number * 10 + (str[i] - '0');
			if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
				return (number * sign);
			i++;
		}
		i++;
	}
	return (0);
}
