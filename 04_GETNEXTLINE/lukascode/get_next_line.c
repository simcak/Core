/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:01:15 by ljiriste          #+#    #+#             */
/*   Updated: 2023/09/12 17:17:04 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// How to free?
// static in get_next_line? So it could be passed to select AND delete
static char	*select_file_buffer(int fd, t_list **list)
{
	t_list	*local_head;

	if (*list == NULL)
	{
		*list = new_ft_node(fd);
		if (list == NULL)
			return (NULL);
		return (((t_ft *)((*list)->content))->buffer);
	}
	local_head = *list;
	while (local_head->next && ((t_ft *)(local_head->content))->fd != fd)
		local_head = local_head->next;
	if (((t_ft *)(local_head->content))->fd == fd)
		return (((t_ft *)(local_head->content))->buffer);
	local_head->next = new_ft_node(fd);
	if (local_head->next == NULL)
		return (NULL);
	return (((t_ft *)(local_head->next->content))->buffer);
}

static void	delete_file_node(int fd, t_list **list)
{
	t_list	*cur;
	t_list	*prev;

	prev = NULL;
	cur = *list;
	while (((t_ft *)(cur->content))->fd != fd)
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev == NULL)
		*list = NULL;
	else
		prev->next = cur->next;
	free(((t_ft *)(cur->content))->buffer);
	free(cur->content);
	free(cur);
	return ;
}

/*	Concatenates res and buffer up to newline.
	Shifts buffer by the transfered characters.
	Returns 0 when buffer is empty (and needs filling with read).
	Also returns 1 when newline is transfered
	unless buffer empty (to delete node).
	Otherwise returns true.
*/
static int	transfer_string(char **res, char *buffer)
{
	int	i;
	int	nl;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	nl = (buffer[i] == '\n');
	i += nl;
	ft_strncat_alloc(res, buffer, i);
	ft_memmove(buffer, buffer + i, BUFFER_SIZE + 1 - i);
	return (buffer[0] && nl);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;
	char			*res;
	int				i;
	static char		*buffer;

	res = NULL;
	buffer = select_file_buffer(fd, &list);
	while (!transfer_string(&res, buffer))
	{
		if (buffer[0] == '\0')
		{
			i = read(fd, buffer, BUFFER_SIZE);
			buffer[i] = '\0';
			if (i <= 0)
				delete_file_node(fd, &list);
			if (i < 0)
			{
				free(res);
				return (NULL);
			}
			if (i == 0)
				return (res);
		}
	}
	return (res);
}
