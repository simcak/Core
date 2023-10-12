/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:26:36 by lwoiton           #+#    #+#             */
/*   Updated: 2023/03/03 15:36:57 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *) s);
	if (start >= s_len)
	{
		start = 0;
		len = 0;
	}
	if (len > (s_len - start))
		len = s_len - start;
	ss = (char *) malloc(len + 1);
	if (!ss)
		return (NULL);
	ft_strlcpy(ss, s + start, len + 1);
	return (ss);
}
