/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:58:24 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 21:13:40 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#define HP	100
#define EP	100
#define AD	30

/*
	is attack function here and in scavtrap necessary?
	why it is not editing the energy points? here and in scavtrap
*/

FragTrap::FragTrap() : ClapTrap() {
	std::cout << BG << "FragTrap default constructor called" << RST << std::endl;
}

FragTrap::FragTrap( const std::string &name ) : ClapTrap( name ) {
	setHitPoints(HP);
	setEnergyPoints(EP);
	setAttackDamage(AD);
	std::cout << BG << "FragTrap constructor called" << RST << std::endl;
}

FragTrap::FragTrap( FragTrap &fragTrap ) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = fragTrap;
}

void	FragTrap::attack( std::string const &target ) {
	std::cout << "FragTrap " << getName() << " attacks " << target << ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

void	FragTrap::highFivesGuys( void ) {
	std::cout << BG << "FragTrap " << getName() << " high five guys!" << RST << std::endl;
}

FragTrap::~FragTrap() {
	std::cout << BR << "FragTrap destructor called" << RST << std::endl;
}

/* ************************************************************  FragTrap.cpp */