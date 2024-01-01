/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:11:30 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 12:23:25 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include "../libft_utils/libft_utils.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int				flag_char(va_list args);
int				flag_string(va_list args);
int				flag_pointer(va_list args);
int				flag_decimal(va_list args);
int				flag_unsigned(va_list args);
int				flag_hex_lower(va_list args);
int				flag_hex_upper(va_list args);
int				flag_percent(void);

unsigned long	ft_find_nbr_size_ptr(unsigned long n);
char			*ft_itoa_ptr(unsigned long n, char char_offset);
char			*ft_itoa(int n);
unsigned int	ft_find_nbr_size(int n);
unsigned int	ft_find_nbr_size_unsigned(unsigned int n);
char			*ft_itoa_unsigned(unsigned int n);
char			*ft_itoa_hex(unsigned int n, char char_offset);

int				printit(char *input);
int				checkflag(char *input);
int				printflag(va_list args, int flagid);
void			printhelper(char *input, int *count);

#endif