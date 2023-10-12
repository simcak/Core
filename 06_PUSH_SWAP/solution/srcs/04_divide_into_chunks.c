/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_divide_into_chunks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:27:23 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 11:16:54 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	set_chunk_nr(t_list *a)
{
	if (a->size <= 5)
		a->chunk_nr = 1;
	else if (a->size > 5 && a->size <= 20)
		a->chunk_nr = 2; 
	else if (a->size > 20 && a->size <= 50)
		a->chunk_nr = 3;
	else if (a->size > 50 && a->size <= 100)
		a->chunk_nr = 4;
	else if (a->size > 100 && a->size <= 200)
		a->chunk_nr = 5;
	else if (a->size > 200 && a->size <= 400)
		a->chunk_nr = 7;
	else if (a->size > 400)
		a->chunk_nr = 8;
	a->chunk_size = (a->size + a->chunk_nr - 1) / a->chunk_nr;
	return (0);
}

int	initiate_chunk_index(t_chnkr *cc)
{
	cc->up_crr_chnk = 0;
	cc->lo_crr_chnk = 1;
	cc->up_chnk_cntr = 0;
	cc->lo_chnk_cntr = 0;
	return (0);
}

int	push_to_low_and_rotate(t_list *a, t_list *b, t_chnkr *cc)
{
	push(b, a);
	if (a->head->next->rank / a->chunk_size > cc->lo_crr_chnk && \
		a->head->next->rank >= (a->size + b->size) - 5)
		rotate2(a, b);
	else
		rotate1(b);
	cc->lo_chnk_cntr++;
	return (0);
}

int	increase_current_chunks(t_list *a, t_chnkr *cc)
{
	if (cc->up_chnk_cntr == a->chunk_size)
	{
		cc->up_chnk_cntr = 0;
		cc->up_crr_chnk += 2;
	}
	else if (cc->lo_chnk_cntr == a->chunk_size)
	{
		cc->lo_chnk_cntr = 0;
		cc->lo_crr_chnk += 2;
	}
	return (0);
}

void	divide_into_chunks(t_list *a, t_list *b)
{
	t_chnkr	cc;

	set_chunk_nr(a);
	initiate_chunk_index(&cc);
	while (a->size > 5)
	{
		if (a->head->rank / a->chunk_size == cc.up_crr_chnk && \
				a->head->rank < (a->size + b->size) - 5)
		{
			push(b, a);
			cc.up_chnk_cntr++;
		}
		else if (a->head->rank / a->chunk_size == cc.lo_crr_chnk && \
				a->head->rank < (a->size + b->size) - 5)
			push_to_low_and_rotate(a, b, &cc);
		else
			rotate1(a);
		increase_current_chunks(a, &cc);
	}
}
