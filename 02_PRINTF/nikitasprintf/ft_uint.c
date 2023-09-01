/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:07:37 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 13:06:40 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putuint(unsigned int n)
{
	if (n > 9)
		putuint(n / 10);
	ft_char(n % 10 + '0');
}

unsigned int	ft_uint(unsigned int n)
{
	putuint(n);
	return (ft_uinumlen(n));
}
