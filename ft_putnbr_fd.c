/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:27:21 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/24 17:20:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[20];
	int		i;
	int		n_is_negative;

	n_is_negative = (n < 0);
	if (n == 0)
		str[0] = '0';
	i = 0;
	while (n != 0)
	{
		str[i++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (n_is_negative)
	{
		str[i] = '-';
	}
	else if (i > 0)
		i--;
	while (i >= 0)
		write(fd, &str[i--], 1);
}
