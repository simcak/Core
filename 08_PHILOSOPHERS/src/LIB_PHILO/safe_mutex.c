/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:54:58 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/01 19:22:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * It is checking us, if we are sending the correct function type.
 */
static int	invalid_type(t_func_type type)
{
	if (type != LOCK && type != UNLOCK && type != INIT && type != DESTROY)
		return (printf("%sInvalid type of mutex function%s\n", R, RST));
	return (SUCCESS);
}

/**
 * Handle error messages for mutex operations from man. It makes the code more
 * robust and easier to maintain.
 */
static int	handle_error(int err, t_func_type type)
{
	if (err == EINVAL && (type == LOCK || type == UNLOCK || type == DESTROY))
		return (printf(R"%s"RST, ERR_EINVAL_MUTEX_LUD));
	if (err == EINVAL && type == INIT)
		return (printf(R"%s"RST, ERR_EINVAL_MUTEX_I));
	if (err == EDEADLK && type == LOCK)
		return (printf(R"%s"RST, ERR_EDEADLK_MUTEX));
	if (err == EPERM && type == UNLOCK)
		return (printf(R"%s"RST, ERR_EPERM_MUTEX));
	if (err == ENOMEM && type == INIT)
		return (printf(R"%s"RST, ERR_ENOMEM_MUTEX));
	if (err == EBUSY && type == DESTROY)
		return (printf(R"%s"RST, ERR_EBUSY_MUTEX));
	return (SUCCESS);
}

/**
 * Safe mutex function to handle mutex operations such as:
 * LOCK, UNLOCK, INIT, DESTROY
 */
int	safe_mutex(t_mutex *mutex, t_func_type type)
{
	int	err;

	if (type == LOCK)
		err = pthread_mutex_lock(mutex);
	if (type == UNLOCK)
		err = pthread_mutex_unlock(mutex);
	if (type == INIT)
		err = pthread_mutex_init(mutex, NULL);
	if (type == DESTROY)
		err = pthread_mutex_destroy(mutex);
	if (invalid_type(type))
		return (FAILURE);
	if (handle_error(err, type))
		return (FAILURE);
	return (SUCCESS);
}
