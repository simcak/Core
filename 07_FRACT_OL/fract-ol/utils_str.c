/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:20 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/23 15:46:34 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
return 1 = true  = input is correct
return 0 = false = input is incorrect
*/
int	correct_input(int ac, char *av[])
{
	if ((ac == 2 && fractol_strncmp(av[1], "mandelbrot", 10))
		|| (ac == 4 && fractol_strncmp(av[1], "julia", 5)))
	{
		return (1);
	}
	return (0);
}
