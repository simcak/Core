/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:58:24 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 11:09:30 by psimcak          ###   ########.fr       */
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
/* ****************** CONSTRUCTORS ****************** */
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

/* ******************** OPERATORS ******************* */
FragTrap	&FragTrap::operator=( FragTrap &fragTrap ) {
	std::cout << "FragTrap assignation operator called" << std::endl;
	if (this != &fragTrap) {
		setName(fragTrap.getName());
		setHitPoints(fragTrap.getHitPoints());
		setEnergyPoints(fragTrap.getEnergyPoints());
		setAttackDamage(fragTrap.getAttackDamage());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	FragTrap::attack( std::string const &target ) {
	std::cout << "FragTrap " << getName() << " attacks " << target << ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

void	FragTrap::highFivesGuys( void ) {
	std::cout << BG << "FragTrap " << getName() << " high five guys!" << RST << std::endl;
}

/* ****************** DESTRUCTOR ******************* */
FragTrap::~FragTrap() {
	std::cout << BR << "FragTrap destructor called" << RST << std::endl;
}

/* ************************************************************  FragTrap.cpp */