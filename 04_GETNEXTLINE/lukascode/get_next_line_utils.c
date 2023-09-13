/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljiriste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:36:53 by ljiriste          #+#    #+#             */
/*   Updated: 2023/09/11 15:22:45 by ljiriste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Functions in this file may (and should) be substituted by Libft functions
	after this project is integrated into Libft
*/

#include <stdlib.h>	// malloc etc.
#include "get_next_line.h"

// This function may be useful enough to add to Libft
void	ft_strncat_alloc(char **dest, char *src, int n)
{
	int		size;
	char	*temp;

	if (n <= 0)
		return ;
	temp = *dest;
	size = 0;
	if (temp)
		while (temp[size])
			++size;
	size += n + 1;
	*dest = malloc(size);
	if (*dest == NULL)
	{
		free(temp);
		return ;
	}
	ft_memmove(*dest, temp, size - n - 1);
	ft_memmove(*dest + size - n - 1, src, n);
	(*dest)[size - 1] = '\0';
	free(temp);
	return ;
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			--i;
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
			++i;
		}
	}
	return (dest);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (res == NULL)
		return (res);
	res->content = content;
	res->next = NULL;
	return (res);
}

t_list	*new_ft_node(int fd)
{
	t_list	*node;
	t_ft	*thread;

	thread = malloc(sizeof(t_ft));
	if (thread == NULL)
		return (NULL);
	node = ft_lstnew(thread);
	if (node == NULL)
	{
		free(thread);
		return (NULL);
	}
	thread->buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (thread->buffer == NULL)
	{
		free(thread);
		free(node);
		return (NULL);
	}
	(thread->buffer)[0] = '\0';
	thread->fd = fd;
	return (node);
}
