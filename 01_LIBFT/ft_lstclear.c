/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:24:52 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/28 16:45:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node_of_list;
	t_list	*next_node;

	if (!lst)
		return ;
	node_of_list = *lst;
	while (node_of_list)
	{
		next_node = node_of_list->next;
		ft_lstdelone(node_of_list, del);
		node_of_list = next_node;
	}
	*lst = NULL;
}
