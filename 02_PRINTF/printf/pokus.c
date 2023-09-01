/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:46:09 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/01 17:16:44 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

void	ft_num_to_str(int num, int *count)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) += 11;
		return ;
	}
	if (num < 0)
	{
		ft_putchar_and_strlen('-', count);
		ft_num_to_str(-num, count);
	}
	else
	{
		if (num >= 10)
			ft_num_to_str(num / 10, count);
		ft_putchar_and_strlen(num % 10 + '0', count);
	}
}

void	ft_putstr(char *str, int *count)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*count) += 6;
		return ;
	}
	while (str[i])
		ft_putchar_and_strlen(str[i++], count);
}

void	ft_u_int_to_str(unsigned int u, int *count)
{
	if (u >= 10)
		ft_u_int_to_str(u / 10, count);
	ft_putchar_and_strlen(u % 10 + '0', count);
}

void	ft_pointer(unsigned long u_int_num, int *count)
{
	char	*str_hex;

	str_hex = "0123456789abcdef";
	// ft_putchar_and_strlen('0', count);
	// ft_putchar_and_strlen('x', count);
	if (u_int_num > 15)
		ft_pointer(u_int_num / 16, count);
	ft_putchar_and_strlen(str_hex[u_int_num % 16], count);
}

void	ft_int_to_hex(char specifier, unsigned int uint_num, int *count)
{
	char	*str_hex;

	if (specifier == 'x')
		str_hex = "0123456789abcdef";
	else
		str_hex = "0123456789ABCDEF";
	if (uint_num >= 16)
		ft_int_to_hex(specifier, uint_num / 16, count);
	ft_putchar_and_strlen(str_hex[uint_num % 16], count);
}

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
		unsigned long	pokus = va_arg(args, unsigned long);
		if (!pokus)
		{
			write(1, "(nil)", 5);
			(*count) += 5;
			return ;
		}	
		ft_putchar_and_strlen('0', count);
		ft_putchar_and_strlen('x', count);
		ft_pointer(pokus, count);
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

int	main(void)
{
	int	len;

	len = ft_printf("FT_PRINTF decimal test: %d \t \t \t", 42);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF char test: %c \t \t \t \t", '@');
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF string test: %s \t \t", "muhahahahaaa");
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF pointer test: %p %p \t \t \t", 0, 3501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF UINT_MAX test: %u \t \t", 4294967295);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF hex-num with low test: %x \t \t", 3501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF hehex-num with up test: %X \t \t", 3501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF percen test: %% \t \t \t");
	ft_printf("-> length is: %i \n", len);
	return (0);
}