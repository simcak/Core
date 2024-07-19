/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:52:20 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/19 18:42:04 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * 🛡 Getters and setters for mutex protected variables 🛡
 * Those functions simply return or set the value of a variable BUT with the
 * mutex protection.
 * When we want to read or write bool or long vars, we lock the mutex so no
 * other thread can access the variable at the same time.
 */

bool	get_bool(t_mutex *mutex, bool *val)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *val;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_bool(t_mutex *mutex, bool *dest, bool val)
{
	safe_mutex(mutex, LOCK);
	*dest = val;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(t_mutex *mutex, long *val)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *val;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mutex *mutex, long *dest, long val)
{
	safe_mutex(mutex, LOCK);
	*dest = val;
	safe_mutex(mutex, UNLOCK);
}

void	increse_long(t_mutex *mutex, long *num)
{
	safe_mutex(mutex, LOCK);
	*num += 1;
	safe_mutex(mutex, UNLOCK);	
}
