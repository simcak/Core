/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:54:47 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/21 18:55:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static  int     count_int(int n)
{
		int count = 0;

		if (n == 0)
		{
				return 1;
		}
		while (n != 0)
		{
				n /= 10;
				count++;
		}
		return (count);
}

static  char    *safe_malloc(int n, int size)
{
		char    *ptr;

		if (n < 0)
		{
				ptr = (char *)malloc(sizeof(char) * (count_int(n) + 2));
				if(!ptr)
						return (NULL);
		}
		else
		{
				ptr = (char *)malloc(sizeof(char) * (count_int(n) + 1));
				if (!ptr)
						return (NULL);
		}
		return (ptr);
}

char *ft_itoa(int n)
{
	char *ptr;
	int index;
	int temp_n = n; // Used to keep the original value of n for later use.

	// Special case for 0
	if (n == 0)
	{
		ptr = safe_malloc(n, 1);
		ptr[0] = '0';
		ptr[1] = '\0';
		return ptr;
	}

	// Special case for INT_MIN
	if (n == INT_MIN)
	{
		return strdup("-2147483648"); // or you can manually convert it without using strdup
	}

	ptr = safe_malloc(n, count_int(n));
	
	if (n < 0)
	{
		*ptr = '-';
		n = -n;
	}
	
	index = count_int(n) - 1;
	while (n > 0)
	{
		ptr[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	
	ptr[count_int(temp_n)] = '\0';
	return ptr;
}

int main()
{
	char *res = ft_itoa(456);
	printf("%s", res);
	free(res); // Free the allocated memory
	return 0;
}