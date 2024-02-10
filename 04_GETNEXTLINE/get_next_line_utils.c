/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:31:11 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/24 17:59:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*joined;
	size_t	s;
	size_t	j;

	s = 0;
	j = 0;
	joined = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!joined)
		return (NULL);
	while (str1 && str1[s])
		joined[j++] = str1[s++];
	s = 0;
	while (str2 && str2[s])
		joined[j++] = str2[s++];
	joined[j] = '\0';
	return (joined);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	alloc_mem_size;
	void	*ptr;

	if (nmemb && ((size_t)(-1) / nmemb) < size)
		return (0);
	alloc_mem_size = nmemb * size;
	ptr = (void *)malloc(alloc_mem_size);
	if (!ptr)
		return (0);
	while (alloc_mem_size && ptr)
		((char *)ptr)[--alloc_mem_size] = 0;
	return (ptr);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int character)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)character)
			return ((char *)(str + i));
		i++;
	}
	if (!character)
		return (&((char *)str)[i]);
	return (NULL);
}

char	*ft_join_and_free(char *str1, char *str2)
{
	char	*str_temp;

	str_temp = ft_strjoin(str1, str2);
	free(str1);
	return (str_temp);
}
