/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:20 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/23 19:38:49 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
return 1 = s1 == s2
return 0 = s1 != s2
that is opposite from original strncmp
*/
int	fractol_strncmp(const char *s1, const char *s2, int n)
{
	if (!s1 || !s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1)
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 - *s2 == 0)
		return (1);
	return (0);
}

// :)
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
with isdup() we are checking if the input from user in julia-case is really
a number and not some random message. It is used only in correct_input_plus_
_set_data.
The function ends with non-digit char and with more than one decimal point.
It does't have to skip empty || extra input. That is handled in func under it.
For bool values, there is # include <stdbool.h>.
*/
static int	isdub(char *s)
{
	bool	has_decimal_point;

	has_decimal_point = false;
	while (*s == ' ' || (*s >= 9 && *s <= 13) || *s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s == '.')
		{
			if (has_decimal_point)
				ft_error_exit(ERROR_DOUBLE);
			has_decimal_point = true;
		}
		else if (!(*s >= '0' && *s <= '9'))
			ft_error_exit(ERROR_DOUBLE);
		s++;
	}
	return (1);
}

/*
return 1 = true  = input is correct
return 0 = false = input is incorrect
printf("%f\n%f\n", ft_atod(av[2]), ft_atod(av[3]));
*/
int	correct_input_plus_set_data(int ac, char *av[], t_fractol *fractal)
{
	if ((ac == 2 && fractol_strncmp(av[1], "mandelbrot", 10))
		|| (ac == 4 && fractol_strncmp(av[1], "julia", 5)))
	{
		fractal->name = av[1];
		if (ac == 4 && isdub(av[2]) && isdub(av[3]))
		{
			fractal->julia_re = ft_atod(av[2]);
			fractal->julia_im = ft_atod(av[3]);
		}
		return (1);
	}
	return (0);
}
