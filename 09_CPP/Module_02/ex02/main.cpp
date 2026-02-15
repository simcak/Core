/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:22 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/22 20:11:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

# define EBS1	"\033[1;34m" << "\t*" << RST
# define EBS2	"\033[1;34m" << "\t\t*" << RST
# define EBS3	"\033[1;34m" << "\t\t\t*" << RST
# define BL		"\033[1;34m" << "-----------------------------\t" << RST

static void	my_tester( void ) {
	Fixed	a2 = Fixed( 7.5f );
	Fixed	b2 = Fixed( 15 );

	std::cout << BB << "*********************************" << RST << std::endl;
	std::cout << BBS << " a2\t\tb2" << EBS2 << std::endl;
	std::cout << BBS << BL << BBS << std::endl;
	std::cout << BBS << a2 << "     >\t" << b2 << ":\t" << (a2 > b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     <\t" << b2 << ":\t" << (a2 < b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     >=\t" << b2 << ":\t" << (a2 >= b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     <=\t" << b2 << ":\t" << (a2 <= b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     ==\t" << b2 << ":\t" << (a2 == b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     !=\t" << b2 << ":\t" << (a2 != b2) << EBS1 << std::endl;
	std::cout << BBS << BL << BBS << std::endl;
	std::cout << BBS << a2 << "     +\t" << b2 << ":\t" << (a2 + b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     -\t" << b2 << ":\t" << (a2 - b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     *\t" << b2 << ":\t" << (a2 * b2) << EBS1 << std::endl;
	std::cout << BBS << a2 << "     /\t" << b2 << ":\t" << (a2 / b2) << EBS1 << std::endl;
	std::cout << BBS << BL << BBS << std::endl;
	std::cout << BBS << BL << BBS << std::endl;

	Fixed	tmp = a2;
	std::cout << BBS << "a2++:\t" << tmp++ << "\t  a2:\t" << tmp << EBS1 << std::endl;
	tmp = a2;
	std::cout << BBS << "++a2:\t" << ++tmp << "\t  a2:\t" << tmp << EBS1 << std::endl;
	tmp = a2;
	std::cout << BBS << "a2--:\t" << tmp-- << "\t  a2:\t" << tmp << EBS1 << std::endl;
	tmp = a2;
	std::cout << BBS << "--a2:\t" << --tmp << "\t  a2:\t" << tmp << EBS1 << std::endl;
	std::cout << BBS << BL << BBS << std::endl;
	std::cout << BBS << "min:\t" << Fixed::min( a2, b2 ) << EBS3 << std::endl;
	std::cout << BBS << "max:\t" << Fixed::max( a2, b2 ) << EBS3 << std::endl;
	std::cout << BB << "*********************************" << RST << std::endl;
}

int	main( void ) {

	Fixed		a;
	Fixed const	b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << "Subject tester" << std::endl;
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max( a, b ) << std::endl;

	my_tester();

	return EXIT_SUCCESS;
}

/******************************************************************  main.cpp */