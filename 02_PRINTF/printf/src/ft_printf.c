/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:28:55 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/01 16:44:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar_and_strlen(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_specifier_clasificator(char specifier, va_list args, int *count)
{
	if (specifier == 'd' || specifier == 'i')
		ft_num_to_str(va_arg(args, int), count);
	else if (specifier == 'c')
		ft_putchar_and_strlen(va_arg(args, int), count);
	else if (specifier == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (specifier == 'p')
	{
		ft_putchar_and_strlen('0', count);
		ft_putchar_and_strlen('x', count);
		ft_pointer(va_arg(args, unsigned long), count);
	}
	else if (specifier == 'u')
		ft_u_int_to_str(va_arg(args, unsigned int), count);
	else if (specifier == 'x' || specifier == 'X')
		ft_int_to_hex(specifier, va_arg(args, unsigned int), count);
	else if (specifier == '%')
		ft_putchar_and_strlen('%', count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
			ft_specifier_clasificator(format[++i], args, &count);
		else
			ft_putchar_and_strlen(format[i], &count);
		i++;
	}
	va_end(args);
	return (count);
}
