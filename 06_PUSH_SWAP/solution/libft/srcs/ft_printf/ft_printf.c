/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:10:06 by luca              #+#    #+#             */
/*   Updated: 2023/05/28 14:23:05 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fs	*init_fs(va_list *args)
{
	t_fs	*fs;

	fs = (t_fs *) malloc(sizeof(t_fs));
	if (!fs)
		return (fs);
	fs->arg = args;
	fs->arg_len = 0;
	fs->spec = 0;
	fs->len = 0;
	fs->hash = 0;
	fs->zero = 0;
	fs->dash = 0;
	fs->space = 0;
	fs->plus = 0;
	fs->width = 0;
	fs->dot = 0;
	fs->precision = 0;
	return (fs);
}

const char	*print_format_specifiers(const char *format, t_fs *fs)
{
	while (*format && flag_check(*format, fs))
		format++;
	while (*format && ft_isdigit(*format))
		fs->width = fs->width * 10 + (int)(*format++ - 48);
	if (*format == '.')
	{
		fs->dot = 1;
		format++;
		if (*format == '-')
			format++;
		while (*format && ft_isdigit(*format))
			fs->precision = fs->precision * 10 + (int)(*format++ - 48);
	}
	specifier_check(*format++, fs);
	return (format);
}

int	flag_check(const char format, t_fs *fs)
{
	if (format == '#')
		fs->hash = 1;
	else if (format == '0')
		fs->zero = 1;
	else if (format == '-')
		fs->dash = 1;
	else if (format == ' ')
		fs->space = 1;
	else if (format == '+')
		fs->plus = 1;
	else
		return (0);
	return (1);
}

int	specifier_check(const char format, t_fs *fs)
{
	fs->spec = (char) format;
	if (format == 'c')
		print_char(fs);
	else if (format == 's')
		print_str(fs);
	else if (format == 'p')
		print_ptr(fs);
	else if (format == 'i')
		print_int(fs);
	else if (format == 'd')
		print_int(fs);
	else if (format == 'u')
		print_uint(fs);
	else if (format == 'x')
		print_uint_hex(fs, 0);
	else if (format == 'X')
		print_uint_hex(fs, 1);
	else if (format == '%')
		print_percent(fs);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	t_fs	*fs;
	va_list	args;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			fs = init_fs(&args);
			format = print_format_specifiers(++format, fs);
			len += fs->len;
			free(fs);
		}
		else
		{
			ft_putchar_fd(*format++, 1);
			len++;
		}
	}
	va_end(args);
	return (len);
}
