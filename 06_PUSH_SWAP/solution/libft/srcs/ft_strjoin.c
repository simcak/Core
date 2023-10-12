/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:35:52 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/04 14:07:10 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*s_joined;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *) s1);
	s2_len = ft_strlen((char *) s2);
	s_joined = (char *) malloc(s1_len + s2_len + 1);
	if (!s_joined)
		return (NULL);
	while (*s1)
		*s_joined++ = *s1++;
	while (*s2)
		*s_joined++ = *s2++;
	*s_joined = '\0';
	return (s_joined - s1_len - s2_len);
}
