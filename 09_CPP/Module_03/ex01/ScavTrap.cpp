/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 19:57:15 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ScavTrap.hpp"

/* ****************** CONSTRACTORS ****************** */
ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << BG << "ScavTrap default constructor called" << RST << std::endl;
}

ScavTrap::ScavTrap( const std::string &name ) : ClapTrap( name ) {
	std::cout << BG << "ScavTrap constructor called" << RST << std::endl;
}

ScavTrap::ScavTrap( ScavTrap &scavTrap ) {
	std::cout << BG << "ScavTrap copy constructor called" << RST << std::endl;
	*this = scavTrap;
}

/* **************** MEMBER FUNCTIONS **************** */
void	ScavTrap::attack( std::string const &target ) {
	std::cout << "ScavTrap " << getName() << " attacks " << target << ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate( void ) {
}

/* ****************** DESTRUCTOR ******************* */
ScavTrap::~ScavTrap() {
	std::cout << BR << "ScavTrap destructor called" << RST << std::endl;
}