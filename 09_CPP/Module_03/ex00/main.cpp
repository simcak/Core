/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 19:26:47 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int		main() {
	ClapTrap	amos("Amos");
	ClapTrap	ben("Ben");

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

	// 3
	ben.attack("Amos");
	amos.takeDamage(ben.getAttackDamage());

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	amos.beRepaired(RP);

	std::cout << std::endl;

	std::cout << amos << "\n" << ben << std::endl;

	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */