/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:55:52 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 17:07:12 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putpointer(unsigned long n, int *size)
{
	char	*set;

	set = "0123456789abcdef";
	if (n >= 16)
		putpointer(n / 16, size);
	ft_char(set[n % 16]);
	(*size)++;
}

int	ft_pointer(unsigned long ptr)
{
	int	len;
	int	size;
	
	if (ptr == 0)
		return (ft_str("(nil)"));
	size = 0;
	len = 0;
	len += write(1, "0x", 2);
	if (ptr == 0)
		len += write(1, "0", 1);
	else
	{
		putpointer(ptr, &size);
		len += size;
	}
	return (len);
}
