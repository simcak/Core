/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:53:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/02 13:37:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * It is checking us, if we are sending the correct function type.
 */
static int	invalid_type(t_func_type type)
{
	if (type != CREATE && type != JOIN && type != DETACH)
		return (printf("%sInvalid type of thread function%s\n", R, RST));
	return (SUCCESS);
}

/**
 * Handle error messages for thread
 * improve readability and maintainability of the code.
 */
static int	handle_error(int err, t_func_type type)
{
	if (type == CREATE && err == EAGAIN)
		return (printf(R"%s"RST, ERR_EAGAIN_THREAD));
	if (type == CREATE && err == EPERM)
		return (printf(R"%s"RST, ERR_EPERM_THREAD));
	if (type == CREATE && err == EINVAL)
		return (printf(R"%s"RST, ERR_EINVAL_THREAD_C));
	if ((type == JOIN || type == DETACH) && err == EINVAL)
		return (printf(R"%s"RST, ERR_EINVAL_THREAD_JD));
	if ((type == JOIN || type == DETACH) && err == ESRCH)
		return (printf(R"%s"RST, ERR_ESRCH_THREAD));
	if (type == JOIN && err == EDEADLK)
		return (printf(R"%s"RST, ERR_EDEADLK_THREAD));
	return (SUCCESS);
}

/**
 * Safe thread function to handle thread operations such as:
 * CREATE, JOIN, DETACH
 */
int	safe_thread(t_thread *thread,
				t_func_type type,
				void *(*func)(void *),
				void *data)
{
	int	err;

	if (type == CREATE)
		err = pthread_create(thread, NULL, func, data);
	if (type == JOIN)
		err = pthread_join(*thread, NULL);
	if (type == DETACH)
		err = pthread_detach(*thread);
	if (invalid_type(type))
		return (FAILURE);
	if (handle_error(err, type))
		return (FAILURE);
	return (SUCCESS);
}
