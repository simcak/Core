/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:24:54 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 14:16:01 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_char_to_nbr(char c, long nbr)
{
	nbr = nbr * 10 + (long)(c - 48);
	return (nbr);
}

long	ft_atoi(const char *nptr)
{
	int		n;
	long	nbr;

	n = 1;
	nbr = 0;
	while (*nptr && (*nptr == 32 || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '-')
	{
		n = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		nbr = ft_char_to_nbr(*nptr, nbr);
		nptr++;
	}
	return (nbr * n);
}
