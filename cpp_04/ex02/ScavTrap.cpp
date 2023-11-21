#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	std::cout << "ScavTrap default constructor." << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_name = name;
	this->_hp = 100;
	this->_energy = 50;
	this->_attack = 20;
	std::cout << "ScavTrap " << this->_name << " has been created by calling constructor." << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "Copy ScavTrap constructor called." << std::endl;

	*this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "Copy ScavTrap assignment operator called." << std::endl;
	this->_name = other._name;
	this->_hp = other._hp;
	this->_energy = other._energy;
	this->_attack = other._attack;

	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->_name << " has been destroyed by calling destructor." << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->_name << " is now in gatekeeper mode." << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (this->_energy < 1)
		std::cout << "ScavTrap" << this->_name << " is attempting to attack " << target << ", but it doesn't have enough energy!" << std::endl;
	if (this->_hp < 1)
		std::cout << "ScavTrap " << this->_name << " cannot attack, it is dead!" << std::endl;
	else
	{
		std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing " << this->_attack << " points of damage!" << std::endl;
		this->_energy -= 1;
	}

}