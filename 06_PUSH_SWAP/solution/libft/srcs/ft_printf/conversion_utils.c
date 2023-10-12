/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:23:47 by lwoiton           #+#    #+#             */
/*   Updated: 2023/05/28 13:24:03 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ultoa(t_fs *fs, unsigned long n, int base, int u_case)
{
	char		str_buf[MAXBUFL];
	static char	digs[] = "0123456789abcdef";
	char		*ptr;

	ptr = &str_buf[MAXBUFL - 1];
	if (!n)
		ft_putchar_len('0', fs);
	while (n)
	{
		if (u_case)
			*(ptr--) = ft_toupper(digs[n % base]);
		else
			*(ptr--) = digs[n % base];
		n /= base;
	}
	write(1, ptr + 1, &str_buf[MAXBUFL - 1] - ptr);
	fs->len += &str_buf[MAXBUFL - 1] - ptr;
	return (0);
}

int	utoa(t_fs *fs, unsigned int n, int base, int u_case)
{
	char		str_buf[MAXBUF];
	static char	digs[] = "0123456789abcdef";
	char		*ptr;

	ptr = &str_buf[MAXBUF - 1];
	if (!n && fs->dot && !fs->precision)
		return (0);
	if (!n)
		ft_putchar_len('0', fs);
	while (n)
	{
		if (u_case)
			*(ptr--) = ft_toupper(digs[n % base]);
		else
			*(ptr--) = digs[n % base];
		n /= base;
	}
	write(1, ptr + 1, &str_buf[MAXBUF - 1] - ptr);
	fs->len += &str_buf[MAXBUF - 1] - ptr;
	return (0);
}

int	get_unsigned_length(t_fs *fs, unsigned int nbr, int base)
{
	if (!nbr && fs->dot && !fs->precision)
		return (0);
	if (!nbr)
		fs->arg_len++;
	while (nbr)
	{
		fs->arg_len++;
		nbr /= base;
	}
	return (0);
}

int	get_ulong_length(t_fs *fs, unsigned long nbr, int base)
{
	if (!nbr)
		fs->arg_len++;
	while (nbr)
	{
		fs->arg_len++;
		nbr /= base;
	}
	return (0);
}
