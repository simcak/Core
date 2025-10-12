/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:39:50 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/12 19:06:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <stdlib.h>

#define MAX_VAL	75

#define BY		"\033[1;33m"
#define BB		"\033[1;34m"
#define RST		"\033[0m"

#define BRERR	"\033[1;31mError: \033[0m"
#define BREXC	"\033[1;31mException: \033[0m"

template <typename T>
class Array {

	private:
		T*				_arr;
		unsigned int	_size;

	public:
		/************************Orthodox Canonical Form***********************/
		Array();
		Array(unsigned int size);
		Array(const Array& copy);
		Array &operator=(const Array &src);
		~Array();

		/************************  ***********************/
		T &operator		[] (unsigned int i);

		/****************************member function***************************/
		unsigned int	size() const;
		void			putArr() const;

		/*******************************exception******************************/
		class IndexOutOfBoundsException : public std::exception {
			public:
				const char*		what() const throw();
		};

};

#include "Array.tpp"

#endif