/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_police.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:49:46 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/04 17:24:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	input_isnt_num(char *str)
{
	if (!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
		return (1);
	if ((*str == '+' || *str == '-') && !(str[1] >= '0' && str[1] <= '9'))
		return (1);
	while (*++str)
		if (!(*str >= '0' && *str <= '9'))
			return (1);
	return (0);
}

int	ft_duplicate_num(t_node *list, int nbr)
{
	if (list == NULL)
		return (0);
	while (list)
	{
		if (list->value == nbr)
			return (1);
		list = list->next;
	}
	return (0);
}

void	ft_free_stack(t_node **list)
{
	t_node	*temp;
	t_node	*head;

	if (list == NULL)
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

void	ft_free_error(t_node **list, char **argv, bool input_string)
{
	ft_free_stack(list);
	if (input_string)
		ft_free_matrix(argv);
	write(2, "Error\n", 6);
	exit(1);
}
