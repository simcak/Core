/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_decimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:57:48 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:30:37 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

unsigned int	ft_find_nbr_size(int n)
{
	unsigned int	size;

	size = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	return (++size);
}

char	*ft_itoa(int n)
{
	char			*output;
	unsigned int	size;
	unsigned int	i;

	size = ft_find_nbr_size(n);
	output = malloc((size + 1) * sizeof(char));
	if (!output)
		return (0);
	if (n == -2147483648)
		return (ft_strcpy(output, "-2147483648"));
	i = 0;
	size--;
	if (n < 0)
	{
		n = -n;
		output[0] = '-';
	}
	while (n >= 10)
	{
		output[size - (i++)] = (n % 10) + '0';
		n = n / 10;
	}
	output[size - i] = (n % 10) + '0';
	output[size + 1] = '\0';
	return (output);
}

int	flag_decimal(va_list args)
{
	int		count;
	char	*tmp_string;

	count = 0;
	tmp_string = ft_itoa(va_arg(args, int));
	count += printit(tmp_string);
	free(tmp_string);
	return (count);
}
