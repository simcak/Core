/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:59:40 by lwoiton           #+#    #+#             */
/*   Updated: 2023/03/03 15:36:41 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*rtnval;

	rtnval = 0;
	while (*s)
	{
		if (*s == (unsigned char) c)
			rtnval = (char *) s;
		s++;
	}
	if (*s == (unsigned char) c)
		return ((char *) s);
	return (rtnval);
}
