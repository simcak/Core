/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:09:57 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 17:28:02 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int n, char format, unsigned int *size)
{
	char	*set;

	if (format == 'x')
		set = "0123456789abcdef";
	else
		set = "0123456789ABCDEF";
	if (n >= 16)
		ft_puthex(n / 16, format, size);
	ft_char(set[n % 16]);
	(*size)++;
}

unsigned int	ft_hex(unsigned int n, char format)
{
	unsigned int	size;

	size = 0;
	ft_puthex(n, format, &size);
	return (size);
}
