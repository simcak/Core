/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 11:09:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ScavTrap.hpp"
#define HP		100
#define EP		50
#define AD		20

/* ****************** CONSTRACTORS ****************** */
ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << BG << "ScavTrap default constructor called" << RST << std::endl;
}

ScavTrap::ScavTrap( const std::string &name ) : ClapTrap( name ) {
	setHitPoints(HP);
	setEnergyPoints(EP);
	setAttackDamage(AD);
	std::cout << BG << "ScavTrap constructor called" << RST << std::endl;
}

ScavTrap::ScavTrap( ScavTrap &scavTrap ) {
	std::cout << BG << "ScavTrap copy constructor called" << RST << std::endl;
	*this = scavTrap;
}

/* ******************** OPERATORS ******************* */
ScavTrap	&ScavTrap::operator=( ScavTrap &scavTrap ) {
	std::cout << "ScavTrap assignation operator called" << std::endl;
	if (this != &scavTrap) {
		setName(scavTrap.getName());
		setHitPoints(scavTrap.getHitPoints());
		setEnergyPoints(scavTrap.getEnergyPoints());
		setAttackDamage(scavTrap.getAttackDamage());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	ScavTrap::attack( std::string const &target ) {
	std::cout << "ScavTrap " << getName() << " attacks " << target << ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate( void ) {
	std::cout << "ScavTrap '" << getName() << "' is from now on a Gate keeper" << std::endl;
}

/* ****************** DESTRUCTOR ******************* */
ScavTrap::~ScavTrap() {
	std::cout << BR << "ScavTrap destructor called" << RST << std::endl;
}

/* ************************************************************  ScavTrap.cpp */