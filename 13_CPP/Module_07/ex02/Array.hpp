/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:39:50 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/13 13:59:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <stdlib.h>

#define MAX_VAL	75

#define BRED	"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define BB		"\033[1;34m"
#define RST		"\033[0m"

#define BRERR	BRED "Error: " RST
#define BREXC	BRED "Exception: " RST

template <typename T>
class Array {

	private:
		T*				_arr;
		unsigned int	_size;

	public:
		/************************Orthodox Canonical Form***********************/
		Array();
		Array(unsigned int n);
		Array(const Array &);
		Array &operator=(const Array &);
		~Array();

		/************************  ***********************/
		T &operator		[] (unsigned int i);

		/****************************member function***************************/
		unsigned int	size() const;
		void			printArr() const;

		/*******************************exception******************************/
		class IndexOutOfBoundsException : public std::exception {
			public:
				const char*		what() const throw();
		};

};

#include "Array.tpp"

#endif