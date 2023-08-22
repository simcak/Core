/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:54:47 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/22 17:07:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_int(int n, int temp_n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (temp_n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*safe_malloc(int n)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (count_int(n, n) + 1));
	if (!ptr)
		return (0);
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		index;
	int		temp_n;

	temp_n = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ptr = safe_malloc(n);
	index = count_int(n, temp_n);
	if (n < 0)
		n = -n;
	index = count_int(n, temp_n) - 1;
	while (n > 0)
	{
		ptr[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	if (temp_n < 0)
		ptr[0] = '-';
	ptr[count_int(temp_n, temp_n)] = 0;
	return (ptr);
}
