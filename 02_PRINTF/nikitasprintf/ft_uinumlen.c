/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uinumlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:05:22 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 13:05:48 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_uinumlen(unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}
