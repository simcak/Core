/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:56:47 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:43:55 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

unsigned long	ft_find_nbr_size_ptr(unsigned long n)
{
	unsigned long	size;

	size = 0;
	while (n != 0)
	{
		n = n / 16;
		size++;
	}
	return (size);
}

char	*ft_itoa_ptr(unsigned long n, char char_offset)
{
	char			*output;
	unsigned long	size;
	unsigned long	i;

	size = ft_find_nbr_size_ptr(n);
	output = malloc((size + 10) * sizeof(char));
	size--;
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
		output[0] = '0';
	else
		output[size + 1] = '\0';
	return (output);
}

int	flag_pointer(va_list args)
{
	int				count;
	unsigned long	f_ptr_param;
	char			*tmp_string;
	char			*tmp_string2;

	count = 0;
	f_ptr_param = va_arg(args, unsigned long);
	tmp_string = NULL;
	tmp_string2 = NULL;
	if (f_ptr_param == 0)
		tmp_string2 = "(nil)";
	else
	{
		tmp_string = ft_itoa_ptr(f_ptr_param, 'a');
		tmp_string2 = ft_strjoin("0x", tmp_string);
	}
	count += printit(tmp_string2);
	free(tmp_string);
	if (f_ptr_param != 0)
		free(tmp_string2);
	return (count);
}
