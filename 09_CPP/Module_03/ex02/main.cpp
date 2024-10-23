/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 14:56:53 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#define RP	5

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
	FragTrap	amos("Amos");
	FragTrap	elvis("Elvis");

	// Tester
	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	amos.attack("Ben");
	elvis.takeDamage(amos.getAttackDamage());

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	elvis.beRepaired(RP);

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	amos.attack("Elvis");
	elvis.takeDamage(amos.getAttackDamage());

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	elvis.beRepaired(RP);

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	elvis.attack("Amos");
	amos.takeDamage(elvis.getAttackDamage());

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	amos.beRepaired(RP);

	std::cout << BBSL << BW << amos << elvis << RST << std::endl;
	elvis.highFivesGuys();

	tester_loop(amos, elvis, true);

	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */