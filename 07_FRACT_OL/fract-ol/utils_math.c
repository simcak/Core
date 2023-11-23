/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:27:52 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/23 18:58:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
scaling the image. we dont change the proportions of the window, but we
calculate "our" index 4 the window size (= 0th pxl is -2, 800th pixel is
2 (when WIDTH = 800) and so on)

(NEW_MAX - NEW_MIN) * (UNSCALED_NUM - OLD_MIN)
----------------------------------------------
        (OLD_MAX - OLD_MIN) + NEW_MIN
*/
double	resize(double k, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (k / old_max) + new_min);
}

/*
sum the real part and sum the imaginary part
*/
t_complex	ft_sum_complex(t_complex z, t_complex c)
{
	t_complex	result;

	result.re = z.re + c.re;
	result.im = z.im + c.im;
	return (result);
}

/*
Square the complex number:		(a + bi)^2
								a^2 + 2abi + b^2 i^2
							re:	a^2 + bi^2
							im:	2 * a * bi
*/
t_complex	ft_sqr_complex(t_complex z)
{
	t_complex	result;

	result.re = (z.re * z.re) - (z.im * z.im);
	result.im = 2 * z.re * z.im;
	return (result);
}

double	ft_atod(char *s)
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
