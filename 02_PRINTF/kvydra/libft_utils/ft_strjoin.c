/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:53:02 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:53:11 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string1;
	char	*string2;
	int		totalsize;
	char	*result;

	string1 = (char *)s1;
	string2 = (char *)s2;
	totalsize = ft_strlen(string1) + ft_strlen(string2) + 1;
	result = (char *)malloc(totalsize);
	if (!result)
		return (0);
	ft_strlcpy(result, string1, ft_strlen(string1) + 1);
	ft_strlcat(result, string2, totalsize);
	return (result);
}
