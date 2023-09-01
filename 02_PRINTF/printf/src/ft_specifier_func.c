/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:35:02 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/01 17:20:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_num_to_str(int num, int *count)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) += 11;
		return ;
	}
	if (num < 0)
	{
		ft_putchar_and_strlen('-', count);
		ft_num_to_str(-num, count);
	}
	else
	{
		if (num >= 10)
			ft_num_to_str(num / 10, count);
		ft_putchar_and_strlen(num % 10 + '0', count);
	}
}

void	ft_putstr(char *str, int *count)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*count) += 6;
		return ;
	}
	while (str[i])
		ft_putchar_and_strlen(str[i++], count);
}

void	ft_u_int_to_str(unsigned int u, int *count)
{
	if (u >= 10)
		ft_u_int_to_str(u / 10, count);
	ft_putchar_and_strlen(u % 10 + '0', count);
}

void	ft_pointer(unsigned long u_int_num, int *count)
{
	char	*str_hex;

	str_hex = "0123456789abcdef";
	if (u_int_num > 15)
		ft_pointer(u_int_num / 16, count);
	ft_putchar_and_strlen(str_hex[u_int_num % 16], count);
}

void	ft_int_to_hex(char specifier, unsigned int uint_num, int *count)
{
	char	*str_hex;

	if (specifier == 'x')
		str_hex = "0123456789abcdef";
	else
		str_hex = "0123456789ABCDEF";
	if (uint_num >= 16)
		ft_int_to_hex(specifier, uint_num / 16, count);
	ft_putchar_and_strlen(str_hex[uint_num % 16], count);
}
