/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:46:54 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/18 12:07:28 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*s1_iter;
	char	*s1_trimmed;

	if (!s1)
		return (NULL);
	if (!set || !*s1)
		return (ft_strdup(s1));
	s1_iter = (char *) s1;
	start = s1_iter;
	while (ft_strchr(set, *s1_iter) != 0 && *s1_iter)
		start = ++s1_iter;
	while (*s1_iter)
		s1_iter++;
	end = s1_iter;
	if (end <= start)
		return (ft_strdup(""));
	while (ft_strrchr(set, *s1_iter) != 0)
		end = s1_iter--;
	s1_trimmed = ft_substr(start, 0, end - start);
	if (!s1_trimmed)
		return (NULL);
	return (s1_trimmed);
}
