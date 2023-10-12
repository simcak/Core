/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:24:19 by lwoiton           #+#    #+#             */
/*   Updated: 2023/05/28 13:27:09 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_len(char *str, t_fs *fs)
{
	ft_putstr_fd(str, 1);
	fs->len += ft_strlen(str);
	return (0);
}

int	ft_putchar_len(char c, t_fs *fs)
{
	ft_putchar_fd(c, 1);
	fs->len++;
	return (0);
}

int	print_flag_hash(t_fs *fs, int u_case)
{
	fs->arg_len += 2;
	if (fs->hash && !u_case)
		ft_putstr_len("0x", fs);
	else if (fs->hash && u_case)
		ft_putstr_len("0X", fs);
	fs->hash = 0;
	return (0);
}

int	print_width(t_fs *fs)
{
	if (fs->dash)
	{
		fs->dash = 0;
		fs->zero = 0;
		return (0);
	}
	while (fs->width > fs->arg_len && fs->width > fs->precision)
	{
		if (fs->zero && !fs->dot)
			ft_putchar_len('0', fs);
		else
			ft_putchar_len(' ', fs);
		fs->width--;
	}
	return (0);
}

int	print_precision(t_fs *fs)
{
	int	count;

	count = fs->precision;
	while (count-- > fs->arg_len)
		ft_putchar_len('0', fs);
	return (0);
}
