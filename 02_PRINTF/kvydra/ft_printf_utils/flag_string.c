/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:55:50 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:32:45 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	flag_string(va_list args)
{
	int		count;
	char	*tmp_string_new;
	char	*tmp_string;

	count = 0;
	tmp_string_new = va_arg(args, char *);
	if (tmp_string_new == NULL)
	{
		tmp_string = "(null)";
	}
	else
	{
		tmp_string = tmp_string_new;
	}
	count += printit(tmp_string);
	return (count);
}
