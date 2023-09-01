/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:14:56 by nandroso          #+#    #+#             */
/*   Updated: 2023/09/01 19:42:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>
#include <stdlib.h>


/*int	ft_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_char(s[i]);
		i++;
	}
	return (i);
}*/

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

/*int main()
{
	int my_test =  ft_printf(" NULL %s NULL ", NULL);
	printf("%i", my_test);
	int libtest = printf(" NULL %s NULL ", NULL);
	printf("%i", libtest);
}*/
