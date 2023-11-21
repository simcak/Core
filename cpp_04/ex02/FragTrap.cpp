#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
	std::cout << "FragTrap default constructor." << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_name = name;
	this->_hp = 100;
	this->_energy = 100;
	this->_attack = 30;
	std::cout << "FragTrap " << this->_name << " has been created by calling constructor." << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "Copy FragTrap constructor called." << std::endl;

	*this = other;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "Copy FragTrap assignment operator called." << std::endl;
	this->_name = other._name;
	this->_hp = other._hp;
	this->_energy = other._energy;
	this->_attack = other._attack;

	return *this;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->_name << " has been destroyed by calling destructor." << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name << " requires to receive a high five! Guys? Anyone?!" << std::endl;
}

void	FragTrap::attack(const std::string& target)
{
	if (this->_energy < 1)
		std::cout << "FragTrap" << this->_name << " is attempting to attack " << target << ", but it doesn't have enough energy!" << std::endl;
	if (this->_hp < 1)
		std::cout << "FragTrap " << this->_name << " cannot attack, it is dead!" << std::endl;
	else
	{
		std::cout << "FragTrap " << this->_name << " attacks " << target << ", causing " << this->_attack << " points of damage!" << std::endl;
		this->_energy -= 1;
	}
}