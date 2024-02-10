/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:31:18 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/19 15:43:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error_exit(char *error_message)
{
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}
