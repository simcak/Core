/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:59:39 by kvydra            #+#    #+#             */
/*   Updated: 2024/01/01 14:13:05 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

char	*ft_itoa_hex(unsigned int n, char char_offset)
{
	char			*output;
	unsigned int	size;
	unsigned int	i;

	size = ft_find_nbr_size_ptr(n);
	output = malloc((size-- + 10) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	while (n != 0)
	{
		if ((n % 16) > 9)
			output[size - (i++)] = ((n % 16) - 10) + char_offset;
		else
			output[size - (i++)] = (n % 16) + '0';
		n = n / 16;
	}
	if (i == 0)
	{
		output[0] = '0';
		output[1] = '\0';
	}
	else
		output[size + 1] = '\0';
	return (output);
}

int	flag_hex_lower(va_list args)
{
	int		count;
	char	*tmp_string;

	count = 0;
	tmp_string = ft_itoa_hex(va_arg(args, int), 'a');
	count += printit(tmp_string);
	if (tmp_string)
		free(tmp_string);
	return (count);
}

int	flag_hex_upper(va_list args)
{
	int		count;
	char	*tmp_string;

	count = 0;
	tmp_string = ft_itoa_hex(va_arg(args, int), 'A');
	count += printit(tmp_string);
	if (tmp_string)
		free(tmp_string);
	return (count);
}
