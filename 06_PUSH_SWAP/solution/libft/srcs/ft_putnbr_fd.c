/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:49:41 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/18 18:52:22 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_nbr_to_str(int n, char *str_buf)
{
	if (n / 10 != 0)
		str_buf = ft_nbr_to_str(n / 10, str_buf);
	else if (n < 0)
		*str_buf++ = '-';
	*str_buf++ = abs(n % 10) + '0';
	*str_buf = '\0';
	return (str_buf);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str_buf[12];

	ft_nbr_to_str(n, str_buf);
	ft_putstr_fd(str_buf, fd);
}
