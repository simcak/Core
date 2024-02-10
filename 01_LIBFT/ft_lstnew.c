/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:09:13 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/28 13:48:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	new -> next = *lst;
// 	*lst = new;
// }

// int main()
// {
// 	t_list *head = NULL;
// 	t_list *new_node = NULL;
// 	int i = 1;
// 	int *data;

// 	// Create and add 5 new nodes with integer content to the list
// 	while (i <= 5)
// 	{
// 		data = malloc(sizeof(int));
// 		*data = i;
// 		new_node = ft_lstnew(data);
// 		ft_lstadd_front(&head, new_node);
// 		i++;
// 	}

// 	// Traverse the list and print the content
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		if (current -> content)
// 		{
// 			printf("Node content: %d\n", *(int *)(current->content));
// 		}
// 		current = current->next;
// 	}

// 	// Free allocated memory and nodes
// 	while (head != NULL)
// 	{
// 		t_list *temp = head;
// 		head = head->next;
// 		free(temp->content);
// 		free(temp);
// 	}

// 	return 0;
// }
