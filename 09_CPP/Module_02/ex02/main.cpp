/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/18 17:54:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main( void ) {

	Fixed		a;
	Fixed const	b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << "*******************************" << std::endl;
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max( a, b ) << std::endl;

	// My tests
	Fixed	a2 = Fixed( 7.5f );
	Fixed	b2 = Fixed( 15 );

	std::cout << "-------------------------------" << std::endl;
	std::cout << a2 << "\t" << b2 << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "a2  >\tb2:\t" << (a2 > b2) << std::endl;
	std::cout << "a2  <\tb2:\t" << (a2 < b2) << std::endl;
	std::cout << "a2  >=\tb2:\t" << (a2 >= b2) << std::endl;
	std::cout << "a2  <=\tb2:\t" << (a2 <= b2) << std::endl;
	std::cout << "a2  ==\tb2:\t" << (a2 == b2) << std::endl;
	std::cout << "a2  !=\tb2:\t" << (a2 != b2) << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "a2  +\tb2:\t" << (a2 + b2) << std::endl;
	std::cout << "a2  -\tb2:\t" << (a2 - b2) << std::endl;
	std::cout << "a2  *\tb2:\t" << (a2 * b2) << std::endl;
	std::cout << "a2  /\tb2:\t" << (a2 / b2) << std::endl;
	std::cout << "-------------------------------" << std::endl;
	Fixed	tmp = a2;
	std::cout << "a2++:\t" << tmp++ << "\t  a2:\t" << tmp << std::endl;
	tmp = a2;
	std::cout << "++a2:\t" << ++tmp << "\t  a2:\t" << tmp << std::endl;
	tmp = a2;
	std::cout << "a2--:\t" << tmp-- << "\t  a2:\t" << tmp << std::endl;
	tmp = a2;
	std::cout << "--a2:\t" << --tmp << "\t  a2:\t" << tmp << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "min:\t" << Fixed::min( a2, b2 ) << std::endl;
	std::cout << "max:\t" << Fixed::max( a2, b2 ) << std::endl;
	std::cout << "*******************************" << std::endl;

	return EXIT_SUCCESS;
}

/******************************************************************  main.cpp */