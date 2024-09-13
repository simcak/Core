/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:10:56 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 12:24:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

int	main( int ac, char **av )
{
	if ( ac != 4) {
		std::cout << BR << ERR_INPUT << "\n" << BW << USAGE << RST << std::endl;
		return EXIT_FAILURE;
	}
	Replace				packet(av[1], av[2], av[3]);

	if (packet.myReplace())
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/* ***************************************************************  main.cpp */