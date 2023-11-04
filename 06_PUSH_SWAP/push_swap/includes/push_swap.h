/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:15 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/04 15:11:31 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>

/*
value: acuall value of the node
rank: rank is the position of the 'value' in the final, sorted output
cost: how far away is 'value' from the 'rank'
*/
typedef struct s_node
{
	int				value;
	int				current_index;
	int				cost;
	bool			up_from_median;
	bool			cheapest;

	struct s_node	*aimed_node;
	struct s_node	*next;
	struct s_node	*prev;

}	t_node;

long	ft_atol(char *argv_i);
char	**ft_split(char *s, char c);
bool	sorted_stack(t_node *list);
void	ft_create_stack(t_node **list, char **argv, bool input_string);
t_node	*ft_find_last_node(t_node *list_head);
int		ft_lstlen(t_node *list);
void	ft_final_rotation(t_node **a);

void	ft_push_swap(t_node **a, t_node **b);
void	ft_baby_sort_3(t_node **head);
void	ft_adult_sort(t_node **a, t_node **b);

void	ft_up_from_median(t_node *list);
void	ft_aim(t_node *a, t_node *b);
void	ft_how_much_it_cost(t_node *a, t_node *b);
t_node	*ft_cheapest(t_node *list);
t_node	*ft_find_smallest(t_node *stack);
void	ft_shoot(t_node **a, t_node **b);

void	ft_free_stack(t_node **list);
void	ft_free_matrix(char **matrix);

void	ft_sa(t_node **a);
void	ft_sb(t_node **b);
void	ft_ss(t_node **a, t_node **b);
void	ft_ra(t_node **a);
void	ft_rb(t_node **b);
void	ft_rr(t_node **a, t_node **b);
void	ft_rra(t_node **a);
void	ft_rrb(t_node **b);
void	ft_rrr(t_node **a, t_node **b);
void	ft_pa(t_node **a, t_node **b);
void	ft_pb(t_node **a, t_node **b);

void	ft_printab(t_node **a, t_node **b);
void	ft_printa(t_node **a);

#endif