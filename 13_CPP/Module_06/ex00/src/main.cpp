/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:10:24 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/03 15:30:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		ScalarConverter::convert(std::string(argv[1]));
	else
		std::cout << BRERR "Wrong number of arguments." << std::endl
		<< "Do: ./<compiled-file> <literal>" << std::endl;
	return 0;
}
