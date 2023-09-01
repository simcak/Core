/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:59:42 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 19:22:20 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>


int		ft_char(int c);
int	ft_str(char *s);
int	ft_int(int n);
int	ft_numlen(int n);
unsigned int	ft_uinumlen(unsigned int n);
unsigned int	ft_uint(unsigned int n);
unsigned int    ft_hex(unsigned int n, char c);
int	ft_pointer(unsigned long ptr);
int	ft_printf(const char *str, ...);


#endif
