/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:27:52 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/19 19:27:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	resize(double k, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (k / old_max) + new_min);
}

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