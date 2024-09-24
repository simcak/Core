/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 19:58:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int		main() {
	ScavTrap	amos("Amos");
	ScavTrap	ben("Ben");

	std::cout << amos << "\n" << ben << std::endl;

	// 1
	amos.attack("Ben");
	ben.takeDamage(amos.getAttackDamage());

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	ben.beRepaired(RP);

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;
	
	// 2
	amos.attack("Ben");
	ben.takeDamage(amos.getAttackDamage());

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	ben.beRepaired(RP);

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */