/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:43:56 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/10 13:01:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main( void ) {
	/************************************INT***********************************/
	std::cout << BY "==================INT===================" RST << std::endl;
	int		a = 22;
	int		b = 11;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl << std::endl;
	
	/**********************************DOUBLE**********************************/
	std::cout << BY "=================DOUBLE=================" RST << std::endl;
	double	a_d = 42.422;
	double	b_d = 42.432;

	::swap( a_d, b_d );
	std::cout << "a = " << a_d << ", b = " << b_d << std::endl;
	std::cout << "min( a, b ) = " << ::min(a_d, b_d) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a_d, b_d) << std::endl << std::endl;
	/***********************************FLOAT**********************************/
	std::cout << BY "==================FLOAT=================" RST << std::endl;
	float	a_f = -81.4f;
	float	b_f = -91.5f;

	::swap( a_f, b_f );
	std::cout << "a = " << a_f << ", b = " << b_f << std::endl;
	std::cout << "min( a, b ) = " << ::min(a_f, b_f) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a_f, b_f) << std::endl << std::endl;

	/**********************************STRING**********************************/
	std::cout << BY "=================STRING=================" RST << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;

	return 0;
}
