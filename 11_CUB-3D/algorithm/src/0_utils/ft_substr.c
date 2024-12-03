/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:03:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/03 16:03:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Function that is used to copy specific part of the string to the new substr.
 */
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
