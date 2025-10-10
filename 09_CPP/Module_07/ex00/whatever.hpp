/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:03:39 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/10 12:52:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

#define BY		"\033[1;33m"
#define RST		"\033[0m"
#define	BRERR	"\033[1;31mError: \033[0m"

template <typename T>
void	swap(T& a, T& b) {
	T	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T	min(T first, T second) { return ((first < second) ? first : second); }

template <typename T>
T	max(T first, T second) { return ((first > second) ? first : second); }

#endif