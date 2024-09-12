/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:54:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 19:17:36 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main( void ) {
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;
	
	std::cout << "Address of the string variable:    " << &str << std::endl;
	std::cout << "Address held by stringPTR:         " << stringPTR << std::endl;
	std::cout << "Address held by stringREF:         " << &stringREF << std::endl;
	
	std::cout << "The value of the string variable:  " << str << std::endl;
	std::cout << "The value pointed to by StringPTR: " << *stringPTR << std::endl;
	std::cout << "The value pointed to by StringREF: " << stringREF << std::endl;

	return EXIT_SUCCESS;
}

/* ***************************************************************** main.cpp */