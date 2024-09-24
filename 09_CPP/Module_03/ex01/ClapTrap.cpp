/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:33 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 19:25:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/* ****************** CONSTRACTORS ****************** */
ClapTrap::ClapTrap() : _name(), _hitPoints(HP), _energyPoints(EP), _attackDamage(AD) {
	std::cout << BG << "ClapTrap default constructor called" << RST << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(HP), _energyPoints(EP), _attackDamage(AD) {
	std::cout << BG << "ClapTrap constructor called" << RST << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &clapTrap) {
	std::cout << BG << "ClapTrap copy constructor called" << RST << std::endl;
	*this = clapTrap;
}

/* **************** MEMBER FUNCTIONS **************** */
void	ClapTrap::attack(const std::string &target) {
	if (!this->getHitPoints() || !this->getEnergyPoints()) {
		std::cout << BR << "ClapTrap " << _name << " is out of necessary points!" << RST << std::endl;
		return ;
	}
	this->setEnergyPoints(this->getEnergyPoints() - 1);
	std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (!this->getHitPoints() || !this->getEnergyPoints()) {
		std::cout << BR << "ClapTrap " << _name << " is out of necessary points!" << RST << std::endl;
		return ;
	}
	this->setHitPoints(this->getHitPoints() - amount);
	std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage!" << std::endl;
	std::cout << "Remaining hit points: " << this->getHitPoints() << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (!this->getHitPoints() || !this->getEnergyPoints()) {
		std::cout << BR << "ClapTrap " << _name << " is out of necessary points!" << RST << std::endl;
		return ;
	}
	this->setHitPoints(this->getHitPoints() + amount);
	this->setEnergyPoints(this->getEnergyPoints() - 1);
	std::cout << "ClapTrap " << _name << " is repaired for " << amount << " points!" << std::endl;
	std::cout << "Remaining hit points: " << this->getHitPoints() << std::endl;
}

/* **************** GETTERS & SETTERS *************** */
std::string	ClapTrap::getName() const {
	return _name;
}

void	ClapTrap::setName(std::string name) {
	_name = name;
}

int	ClapTrap::getHitPoints() const {
	return _hitPoints;
}

void	ClapTrap::setHitPoints(int hitPoints) {
	_hitPoints = hitPoints;
}

int	ClapTrap::getEnergyPoints() const {
	return _energyPoints;
}

void	ClapTrap::setEnergyPoints(int energyPoints) {
	_energyPoints = energyPoints;
}

int	ClapTrap::getAttackDamage() const {
	return _attackDamage;
}

void	ClapTrap::setAttackDamage(int attackDamage) {
	_attackDamage = attackDamage;
}

std::ostream	&operator<<(std::ostream &stream, ClapTrap &clapTrap) {
	stream << "Name: \t\t\t" << clapTrap.getName() << "\n" << \
	" Hitpoints: \t\t" << clapTrap.getHitPoints() << "\n" << \
	" Energy Points: \t" << clapTrap.getEnergyPoints() << "\n" << \
	" Attack Damage: \t" << clapTrap.getAttackDamage();
	stream << std::endl;
	return stream;
}

/* ******************* DESTRUCTOR ******************* */
ClapTrap::~ClapTrap() {
	std::cout << BR << "ClapTrap destructor called" << RST << std::endl;
}

/* ************************************************************  ClapTrap.cpp */