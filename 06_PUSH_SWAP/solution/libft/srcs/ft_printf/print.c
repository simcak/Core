/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:13:35 by luca              #+#    #+#             */
/*   Updated: 2023/05/28 13:23:17 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_fs *fs)
{
	fs->arg_len++;
	print_width(fs);
	ft_putchar_len(va_arg(*(fs->arg), int), fs);
	print_width(fs);
	return (0);
}

int	print_str(t_fs *fs)
{
	char	*str;

	str = va_arg(*(fs->arg), char *);
	if (!str)
		fs->arg_len = 6;
	else
		fs->arg_len = ft_strlen(str);
	if (str && fs->dot && fs->precision < fs->arg_len)
		fs->arg_len = fs->precision;
	if (str && fs->dot && fs->precision > fs->arg_len)
		fs->precision = fs->arg_len;
	print_width(fs);
	if (!str && (!fs->dot || fs->precision >= fs->arg_len))
		ft_putstr_len("(null)", fs);
	if (str && !fs->dot)
		ft_putstr_len(str, fs);
	else if (str && fs->dot)
	{
		while (*str && fs->arg_len--)
			ft_putchar_len(*str++, fs);
	}
	print_width(fs);
	return (0);
}

int	print_ptr(t_fs *fs)
{
	long unsigned int	ptr;

	ptr = va_arg(*(fs->arg), long unsigned int);
	if (!ptr)
		fs->arg_len = 5;
	else
	{
		get_ulong_length(fs, ptr, 16);
		fs->arg_len += 2;
	}
	print_width(fs);
	if (!ptr)
		ft_putstr_len("(nil)", fs);
	else
	{
		ft_putstr_len("0x", fs);
		ultoa(fs, ptr, 16, 0);
	}
	print_width(fs);
	return (0);
}

int	print_uint(t_fs *fs)
{
	unsigned int	nbr;

	nbr = va_arg(*(fs->arg), unsigned int);
	get_unsigned_length(fs, nbr, 10);
	print_width(fs);
	print_precision(fs);
	utoa(fs, nbr, 10, 0);
	print_width(fs);
	return (0);
}

int	print_uint_hex(t_fs *fs, int u_case)
{
	unsigned int	nbr;

	nbr = va_arg(*(fs->arg), unsigned int);
	get_unsigned_length(fs, nbr, 16);
	if (nbr && fs->hash && fs->zero)
		print_flag_hash(fs, u_case);
	print_width(fs);
	if (nbr && fs->hash)
		print_flag_hash(fs, u_case);
	print_precision(fs);
	utoa(fs, nbr, 16, u_case);
	print_width(fs);
	return (0);
}
