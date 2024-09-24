/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 20:43:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int		main() {
	ScavTrap	amos("Amos");
	ScavTrap	ben("Ben");

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	amos.attack("Ben");
	ben.takeDamage(amos.getAttackDamage());

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	ben.beRepaired(RP);

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	ben.guardGate();

	std::cout << std::endl;


	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */