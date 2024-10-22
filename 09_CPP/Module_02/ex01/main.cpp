/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/22 19:36:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

static void	tester(	const Fixed& a, const Fixed& b,
					const Fixed& c, const Fixed& d )
{
	std::cout << BBLUE << "Basic checks:" << RST << std::endl;
	std::cout << "\ta is: " << a << std::endl;
	std::cout << "\tb is: " << b << std::endl;
	std::cout << "\tc is: " << c << std::endl;
	std::cout << "\td is: " << d << std::endl;
	
	std::cout << BWHITE << "************************" << RST << std::endl;
	std::cout << BBLUE << "to Int convertion:" << RST << std::endl;
	std::cout << "\ta is: " << a.toInt() << " as integer" << std::endl;
	std::cout << "\tb is: " << b.toInt() << " as integer" << std::endl;
	std::cout << "\tc is: " << c.toInt() << " as integer" << std::endl;
	std::cout << "\td is: " << d.toInt() << " as integer" << std::endl;
	
	std::cout << BWHITE << "************************" << RST << std::endl;
	std::cout << BBLUE << "to Float convertion:" << RST << std::endl;
	std::cout << "\ta is: " << a.toFloat() << " as float" << std::endl;
	std::cout << "\tb is: " << b.toFloat() << " as float" << std::endl;
	std::cout << "\tc is: " << c.toFloat() << " as float" << std::endl;
	std::cout << "\td is: " << d.toFloat() << " as float" << std::endl;

	return ;
}

/**
 * Each of the created Fixed variables are an **instances** of the Fixed class.
 */
int	main( void ) {

	Fixed		a;
	Fixed const	b( 10 );
	Fixed const	c( 42.42f );
	Fixed const	d( b );

	a = Fixed( 1234.4321f );

	tester(a, b, c, d);

	return EXIT_SUCCESS;
}

/******************************************************************  main.cpp */