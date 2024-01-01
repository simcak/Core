/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:51:57 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 12:26:45 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	flag_char(va_list args)
{
	char	tmp;

	tmp = va_arg(args, int);
	write(1, &tmp, 1);
	return (1);
}
