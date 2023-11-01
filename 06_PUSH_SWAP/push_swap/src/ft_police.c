/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_police.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:49:46 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/01 18:05:47 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_free_stack(t_node **list)
{
	t_node	*temp;
	t_node	*head;

	if (NULL == list)
		return ;
	head = *list;
	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	*list = NULL;
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix == NULL || *matrix == NULL)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix - 1);
}
