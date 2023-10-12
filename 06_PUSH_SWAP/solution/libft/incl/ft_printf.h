/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:18:42 by lwoiton           #+#    #+#             */
/*   Updated: 2023/05/25 17:24:54 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define MAXBUF 128
# define MAXBUFL 128
# define MIN_INT -2147483648

typedef struct fs{
	va_list	*arg;
	int		arg_len;
	char	spec;
	int		len;
	int		hash;
	int		zero;
	int		dash;
	int		space;
	int		plus;
	int		width;
	int		dot;
	int		precision;
}	t_fs;

t_fs		*init_fs(va_list *args);
const char	*print_format_specifiers(const char *format, t_fs *fs);
int			flag_check(const char format, t_fs *fs);
int			specifier_check(const char format, t_fs *fs);
int			ft_printf(const char *format, ...);
int			print_char(t_fs *fs);
int			print_str(t_fs *fs);
int			print_ptr(t_fs *fs);
int			print_int(t_fs *fs);
char		*print_int_handle_flags(t_fs *fs, int nbr, char *str);
int			print_uint(t_fs *fs);
int			print_uint_hex(t_fs *fs, int u_case);
int			print_percent(t_fs *fs);
int			utoa(t_fs *fs, unsigned int n, int base, int u_case);
int			ultoa(t_fs *fs, unsigned long n, int base, int u_case);
int			print_flag_hash(t_fs *fs, int u_case);
int			ft_putstr_len(char *str, t_fs *fs);
int			ft_putchar_len(char c, t_fs *fs);
int			get_unsigned_length(t_fs *fs, unsigned int nbr, int base);
int			get_ulong_length(t_fs *fs, unsigned long nbr, int base);
int			print_flag_zero(t_fs *fs);
int			print_precision(t_fs *fs);
int			get_formatted_length(t_fs *fs);
int			print_width(t_fs *fs);
#endif
