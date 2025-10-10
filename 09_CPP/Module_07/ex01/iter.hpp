/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:29 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/10 17:33:01 by psimcak          ###   ########.fr       */
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
template <typename T>
void	iter(T* arr, size_t length, void (*func)(T&)) {
	for (size_t i = 0; i < length; ++i)
		func(arr[i]);
}

// practically the same but without the function
// purpose: just print out what do we work with in the 'iter' function
template <typename T>
void	printArr(T *arr, size_t length) {
	for (size_t i = 0; i < length; ++i)
		std::cout << "[" << arr[i] << "], ";
}

#endif