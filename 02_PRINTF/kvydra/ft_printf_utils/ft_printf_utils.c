/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:10:40 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 12:27:56 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	printit(char *input)
{
	int	count;

	count = 0;
	while (*input != '\0')
	{
		write(1, input, 1);
		input++;
		count++;
	}
	return (count);
}

int	checkflag(char *input)
{
	int	rtval;

	rtval = -1;
	if (!ft_strncmp(input, "%c", 2))
		rtval = 1;
	else if (!ft_strncmp(input, "%s", 2))
		rtval = 2;
	else if (!ft_strncmp(input, "%p", 2))
		rtval = 3;
	else if (!ft_strncmp(input, "%d", 2))
		rtval = 4;
	else if (!ft_strncmp(input, "%i", 2))
		rtval = 4;
	else if (!ft_strncmp(input, "%u", 2))
		rtval = 5;
	else if (!ft_strncmp(input, "%x", 2))
		rtval = 7;
	else if (!ft_strncmp(input, "%X", 2))
		rtval = 8;
	else if (!ft_strncmp(input, "%%", 2))
		rtval = 9;
	return (rtval);
}

int	printflag(va_list args, int flagid)
{
	int	count;

	count = 0;
	if (flagid == 1)
		count += flag_char(args);
	if (flagid == 2)
		count += flag_string(args);
	if (flagid == 3)
		count += flag_pointer(args);
	if (flagid == 4)
		count += flag_decimal(args);
	if (flagid == 5)
		count += flag_unsigned(args);
	if (flagid == 7)
		count += flag_hex_lower(args);
	if (flagid == 8)
		count += flag_hex_upper(args);
	if (flagid == 9)
		count += flag_percent();
	return (count);
}

void	printhelper(char *input, int *count)
{
	write(1, input, 1);
	(*count)++;
}
