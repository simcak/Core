/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:24:53 by lwoiton           #+#    #+#             */
/*   Updated: 2023/05/28 13:25:39 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_percent(t_fs *fs)
{
	ft_putchar_len('%', fs);
	return (0);
}

int	print_int(t_fs *fs)
{
	int		nbr;
	char	*str;
	char	*start;

	nbr = va_arg(*(fs->arg), int);
	start = ft_itoa(nbr);
	fs->arg_len = ft_strlen (start);
	str = print_int_handle_flags(fs, nbr, start);
	print_precision(fs);
	if (!(fs->dot && !fs->precision && nbr == 0))
		ft_putstr_len(str, fs);
	else
		fs->arg_len = 0;
	print_width(fs);
	if (start != str)
		free(--str);
	else
		free(str);
	return (0);
}

char	*print_int_handle_flags(t_fs *fs, int nbr, char *str)
{
	if (fs->space && !fs->plus && nbr >= 0)
		ft_putchar_len(' ', fs);
	if (fs->plus && nbr >= 0)
		ft_putchar_len('+', fs);
	if (fs->dot && fs->zero && nbr < 0 && nbr % 10 == 0)
		fs->width--;
	if (fs->zero && !fs->dot && nbr < 0)
	{
		ft_putchar_len('-', fs);
		str++;
	}
	print_width(fs);
	if (fs->dot && nbr < 0)
	{
		ft_putchar_len('-', fs);
		fs->precision++;
		str++;
	}
	return (str);
}
