/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:52:35 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/21 21:52:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/** 
 * 1) Initialize argv && the list of all philosophers
 */
int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (argc == 5 || argc == 6)
	{
		if (prepare_dinner(&dinner, argv))
			return (FAILURE);
		printf("%sDinner prepared successfully%s\n", G, RST);
		if (start_dinner(&dinner))
			return (FAILURE);
		// clean(&dinner);			// TODO
	}
	else
		return (printf("%sError: wrong number of arguments%s\n", R, RST));
	return (SUCCESS);
}
