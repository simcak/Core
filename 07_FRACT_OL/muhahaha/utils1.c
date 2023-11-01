/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:58:13 by nandroso          #+#    #+#             */
/*   Updated: 2023/10/31 17:58:19 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.i = z1.i + z2.i;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.i * z.i);
	result.i = 2 * z.real * z.i;
	return (result);
}

double	atod(char *s)
{
	double	fraction;
	double	pow;
	int		sign;
	int		integer_part;

	integer_part = 0;
	fraction = 0;
	sign = +1;
	pow = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10;
		fraction = fraction + (*s++ - 48) * pow;
	}
	return ((integer_part + fraction) * sign);
}

double	map(double unsc_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unsc_num - 0) / (old_max - 0) + new_min);
}

void	error(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		write(STDERR_FILENO, &*str, 1);
		str++;
	}
	exit(EXIT_FAILURE);
}
