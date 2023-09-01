/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:27:29 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/01 17:35:36 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
void	ft_putchar_and_strlen(char c, int *count);
void	ft_specifier_clasificator(char specifier, va_list args, int *count);
void	ft_num_to_str(int num, int *count);
void	ft_putstr(char *str, int *count);
void	ft_u_int_to_str(unsigned int u, int *count);
void	ft_int_to_hex(char specifier, unsigned int uint_num, int *count);
void	ft_pointer(unsigned long u_int_num, int *count);

#endif
