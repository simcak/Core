/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 14:40:30 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

static void	tester_loop(ClapTrap &amos, ClapTrap &ben, bool run_condition) {
	if (run_condition) {
		std::cout << BO << "\nLOOPloopLOOPloopLOOP" << RST << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << BBSL << BW << amos << ben << RST << std::endl;
			amos.attack("Ben");
			ben.takeDamage(amos.getAttackDamage());
		}
	}
	return ;
}

int		main() {
	ClapTrap	amos("Amos");
	ClapTrap	ben("Ben");

	// Tester
	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	amos.attack("Ben");
	ben.takeDamage(amos.getAttackDamage());

	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	ben.beRepaired(RP);

	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	amos.attack("Ben");
	ben.takeDamage(amos.getAttackDamage());

	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	ben.beRepaired(RP);

	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	ben.attack("Amos");
	amos.takeDamage(ben.getAttackDamage());

	std::cout << BBSL << BW << amos << ben << RST << std::endl;
	amos.beRepaired(RP);

	std::cout << BBSL << BW << amos << ben << RST << std::endl;

	tester_loop(amos, ben, true);

	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */