/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:53:46 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/04 17:32:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strnstr(const char *str, const char *sub_string, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (0);
	if (!sub_string[0])
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (i + j < len && str[i + j] == sub_string[j] && sub_string[j])
			j++;
		if (!sub_string [j])
			return ((char *)str + i);
		i++;
	}
	return (0);
}
