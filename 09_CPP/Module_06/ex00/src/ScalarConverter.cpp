/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:28 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/03 15:27:24 by psimcak          ###   ########.fr       */
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
static bool	okChar(double d) {
	return (std::isfinite(d) && d >= 0.0 && d <= 127.0 && std::floor(d) == d);
}

static bool	okInt(double d) {
	return (std::isfinite(d) &&
			d >= static_cast<double>(INT_MIN) &&
			d <= static_cast<double>(INT_MAX));
}

static void printOutFromDouble(double d) {
	// CHAR
	if (okChar(d)) {
		char c = static_cast<char>(d);
		if (std::isprint(static_cast<unsigned char>(c)))
			std::cout << "char:  \t" << '\'' << c << '\'' << std::endl;
		else
			std::cout << "char:  \tnon-displayable" << std::endl;
	} else
		std::cout << "char:  \timpossible" << std::endl;

	// INT
	if (okInt(d))
		std::cout << "int:   \t" << static_cast<int>(d) << std::endl;
	else
		std::cout << "int:   \timpossible" << std::endl;

	// FLOAT
	if (std::isnan(d))
		std::cout << "float: \tnanf" << std::endl;
	else if (d ==  std::numeric_limits<double>::infinity())
		std::cout << "float: \t+inff" << std::endl;
	else if (d == -std::numeric_limits<double>::infinity())
		std::cout << "float: \t-inff" << std::endl;
	else if (std::fabs(d) > static_cast<double>(std::numeric_limits<float>::max()))
		std::cout << "float: \timpossible" << std::endl;
	else {
		float f = static_cast<float>(d);
		if (std::floor(d) == d)
			std::cout << "float: \t" << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		else
			std::cout << "float: \t" << std::setprecision(std::numeric_limits<float>::digits10) << f << "f" << std::endl;
	}

	// DOUBLE
	if (std::isnan(d))
		std::cout << "double:\tnan" << std::endl;
	else if (d ==  std::numeric_limits<double>::infinity())
		std::cout << "double:\t+inf" << std::endl;
	else if (d == -std::numeric_limits<double>::infinity())
		std::cout << "double:\t-inf" << std::endl;
	else {
		if (std::floor(d) == d)
			std::cout << "double:\t" << std::fixed << std::setprecision(1) << d << std::endl;
		else
			std::cout << "double:\t" << std::setprecision(std::numeric_limits<double>::digits10) << d << std::endl;
	}
}

/*******************************member functions*******************************/
void ScalarConverter::convert(std::string literal) {
	// try CHAR - if good, return
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') {
		char c = literal[1];
		printOutFromDouble(static_cast<double>(c));
		return;
	}
	if (literal.length() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0]))) {
		char c = literal[0];
		printOutFromDouble(static_cast<double>(c));
		return;
	}

	// try NUMBER
	char*	end = 0;
	double	d = std::strtod(literal.c_str(), &end);
	bool	okSyntax = (*end == '\0') || (*end == 'f' && *(end + 1) == '\0');
	bool	pseudoOk = false;

	// try PSEUDO-LETERALS
	if (!okSyntax) {
		if (literal == "nan" || literal == "nanf") {
			d = std::numeric_limits<double>::quiet_NaN();
			pseudoOk = true;
		} else if (literal == "+inf" || literal == "+inff") {
			d =  std::numeric_limits<double>::infinity();
			pseudoOk = true;
		} else if (literal == "-inf" || literal == "-inff") {
			d = -std::numeric_limits<double>::infinity();
			pseudoOk = true;
		}
		if (!pseudoOk) {
			std::cout	<< "char:  \timpossible\n"
						<< "int:   \timpossible\n"
						<< "float: \timpossible\n"
						<< "double:\timpossible\n";
			return;
		}
	}

	printOutFromDouble(d);
}
