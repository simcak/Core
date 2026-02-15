/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:30:04 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/20 16:16:44 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv)
{
	Harl	harl;

	if (argc != 2) {
		harl.complain("irrelevant input");
		return EXIT_FAILURE;
	}
	harl.complain(argv[1]);
	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */