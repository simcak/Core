/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:54:11 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/21 15:54:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_atol(char *argv_i)
{
	long	output_num;
	int		sign;
	int		i;

	output_num = 0;
	sign = 1;
	i = 0;
	while (argv_i[i] && 
			(argv_i[i] == ' ' || argv_i[i] == '\n' || argv_i[i] == '\t' 
			|| argv_i[i] == '\v' || argv_i[i] == '\f' || argv_i[i] == '\r'))
		i++;
	if (argv_i[i] == '+')
		i++;
	else if (argv_i[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (argv_i[i] >= '0' && argv_i[i] <= '9')
		output_num = (output_num * 10) + (argv_i[i++] - '0');
	output_num *= sign;
	return (output_num);
}
