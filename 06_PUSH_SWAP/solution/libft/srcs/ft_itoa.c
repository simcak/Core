/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:04 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/18 16:19:52 by lwoiton          ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	str_buf[12];
	char	*n_str;

	ft_nbr_to_str(n, str_buf);
	n_str = (char *) malloc(ft_strlen(str_buf) + 1);
	if (!n_str)
		return (NULL);
	ft_strlcpy(n_str, str_buf, ft_strlen(str_buf) + 1);
	return (n_str);
}
