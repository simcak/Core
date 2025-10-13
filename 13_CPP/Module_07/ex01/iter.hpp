/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:29 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/13 15:38:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>

#define BY		"\033[1;33m"
#define BB		"\033[1;34m"
#define RST		"\033[0m"
#define BRERR	"\033[1;31mError: \033[0m"

/***********************************template***********************************/
template <typename T, typename Func>
void	iter(T *arr, size_t length, void (*func)(Func &)) {
	for (size_t i = 0; i < length; ++i)
		func(arr[i]);
}

#endif