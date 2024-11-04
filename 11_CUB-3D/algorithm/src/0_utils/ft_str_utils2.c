/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:19:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 13:00:40 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Concatenates two strings
 * 
 * The strjoin() function allocates and returns a new string, which is the
 * result of the concatenation of 's1' and 's2'.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*output_str;
	unsigned int	combined_len;

	if (!s1 || !s2)
		return (NULL);
	combined_len = ft_strlen(s1) + ft_strlen(s2);
	output_str = (char *) malloc(sizeof(char) * (combined_len + 1));
	if (!output_str)
		return (NULL);
	ft_strlcpy(output_str, s1, combined_len + 1);
	ft_strlcat(output_str, s2, combined_len + 1);
	return (output_str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;

	if (!str)
		return (0);
	if (start >= ft_strlen(str))
	{
		len = 0;
		start = ft_strlen(str);
	}
	else if (len > ft_strlen(&str[start]))
		len = ft_strlen(&str[start]);
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	ft_strlcpy(substr, &str[start], len + 1);
	return (substr);
}
