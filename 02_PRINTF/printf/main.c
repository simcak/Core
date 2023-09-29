/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:00:15 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/29 15:43:34 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>


int	main(void)
{
	int	len;

	len = ft_printf("FT_PRINTF decimal test: %d \t \t \t", 42);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF char test: %c \t \t \t \t", '@');
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF string test: %s \t \t", "muhahahahaaa");
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF pointer test: %p \t \t \t", 501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF UINT_MAX test: %u \t \t", 4294967295);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF hex-num with low test: %x \t \t", 3501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF hehex-num with up test: %X \t \t", 3501);
	ft_printf("-> length is: %i \n", len);
	len = ft_printf("FT_PRINTF percen test: %% \t \t \t \n");
	ft_printf("Maximum pro náš print: %d \n", INT_MAX);
	printf("Maximum pro origo print: %d \n", INT_MAX);
	ft_printf("Minimum pro náš print: %d \n", INT_MIN);
	printf("Maximum pro origo print: %d \n", INT_MIN);
	return (0);
}
