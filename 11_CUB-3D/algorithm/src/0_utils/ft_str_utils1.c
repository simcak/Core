/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:19:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 12:48:15 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Calculate the length of a string
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Compare two strings
 * If the strings are equal, the function returns 0.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

/**
 * @brief Duplicates a string
 * 
 * The strdup() function allocates sufficient memory for a copy of the string s1,
 * does the copy, and returns a pointer to it.
 */
char	*ft_strdup(const char *str)
{
	char	*output;
	int		len;
	int		i;

	len = ft_strlen(str);
	output = (char *) malloc(sizeof(char) * (len + 1));
	if (!output)
		return (0);
	i = -1;
	while (str[++i] != '\0')
		output[i] = str[i];
	output[i] = '\0';
	return (output);
}

/**
 * @brief Copy a string from src to dst
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > i)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/**
 * @brief Concatenates two strings, no memory allocation
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	if (!dest && size == 0)
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size == 0 || size <= dest_len)
		return (src_len + size);
	i = 0;
	while (src[i] != '\0' && i < size - dest_len - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
