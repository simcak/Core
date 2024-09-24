/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 21:05:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#define RP	5

int		main() {
	FragTrap	amos("Amos");
	FragTrap	elvis("Elvis");

	std::cout << std::endl;

	std::cout << amos << "\n" << elvis << std::endl;

	amos.attack("Elvis");
	elvis.takeDamage(amos.getAttackDamage());

	std::cout << std::endl;

	std::cout << amos << "\n" << elvis << std::endl;

	elvis.beRepaired(5);

	std::cout << std::endl;

	std::cout << amos << "\n" << elvis << std::endl;

	elvis.highFivesGuys();

	std::cout << std::endl;

	return EXIT_SUCCESS;
}

/* ****************************************************************  main.cpp */