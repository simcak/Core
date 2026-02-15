/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:01 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/03 15:31:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

#include <stdlib.h>	// strtod
#include <iomanip>	// setprecision
#include <climits>	// INT_MAX
#include <limits>	// std::numeric_limits
#include <cfloat>	// FLT,DBL_MAX
#include <cmath>
#include <string>
#include <iostream>

#include "Macros.hpp"

/**
 * STATIC UTILITY CLASS in C++:
 * There is no "static class" in C++, so we need to simulate it.
 * A static class in C++ is a class that has:
 * - only static methods
 * - no public constructor
 * It is intended to be used as a namespace.
 * It is not possible to instantiate an object of that class.
 * We can call the static methods of the class without creating an object of that class.
 */
class ScalarConverter
{
	private:
		/************************Orthodox Canonical Form***********************/
		ScalarConverter();
		ScalarConverter(const ScalarConverter &);
		ScalarConverter &operator=(const ScalarConverter &);
		~ScalarConverter();

	public:
		/****************************member function***************************/
		static void	convert(std::string literal);

		/**********************************************************************/
};

#endif
