/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:19:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:55:48 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
