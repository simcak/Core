/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:28 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/01 19:55:56 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

/***************************Orthodox Canonical Form****************************/
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other) { *this=other; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

/*******************************helper functions*******************************/
static void	printOut(int i, float f, double d) {
	if (i >= 0 && i <= 127) {
		char c = static_cast<char>(i);

		if (isprint(c))
			std::cout << "char:  \t" << c << std::endl;
		else
			std::cout << "char:  \tnon-displayable" << std::endl;
	}
	else
		std::cout << "char:  \timpossible" << std::endl;
	std::cout << "int:   \t" << i << std::endl;
	std::cout << "float: \t" << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	std::cout << "double:\t" << std::fixed << std::setprecision(1) << d << std::endl;
}

/*******************************member functions*******************************/
void	ScalarConverter::convert(std::string literal) {
	std::cout << "literal: \"" << literal << "\"" << std::endl;
	std::cout << "length : " << literal.length() << std::endl << std::endl;

	// try CHARACTER
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') {
		char	c = literal[1];
		printOut(static_cast<int>(c), static_cast<float>(c), static_cast<double>(c));
	}
	else if (literal.length() == 1 && !isdigit(literal[0])) {
		char	c = literal[0];
		printOut(static_cast<int>(c), static_cast<float>(c), static_cast<double>(c));
	}

	// try NUMBERS by converting literal to double
	char	*end;
	double	d = std::strtod(literal.c_str(), &end);
	std::cout << "double:\t" << d << std::endl
	<< "end:\t" << end << std::endl << std::endl;

	if (*end == '\0' || (*end == 'f' && *(end+1) == '\0')) {
		int i = static_cast<int>(d);
		if (i >= 0 && i <= 127) {
			char c = static_cast<char>(i);

			if (isprint(c))
				std::cout << "char:  \t" << c << std::endl;
			else
				std::cout << "char:  \tnon-displayable" << std::endl;
		}
		else std::cout << "char:  \timpossible" << std::endl;

		if (d >= INT_MIN && d <= INT_MAX)
			std::cout << "int:   \t" << i << std::endl;
		else std::cout << "int:   \timpossible" << std::endl;

		if (d >= -FLT_MAX && d <= FLT_MAX) {
			float f = static_cast<float>(d);
			std::cout << "float: \t" << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		}
		else std::cout << "float: \timpossible" << std::endl;
		
		std::cout << "double:\t" << std::fixed << std::setprecision(1) << d << std::endl;
	}
	// if (d >= -DBL_MAX || d <= DBL_MAX) // <- need to check double extremes
}
