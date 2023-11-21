#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{}

ClapTrap::ClapTrap(std::string name)
{
	this->_name = name;
	this->_hp = 10;
	this->_energy = 10;
	this->_attack = 0;
	std::cout << "ClapTrap " << this->_name << " has been created by calling constructor." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	std::cout << "Copy ClapTrap constructor called." << std::endl;

	*this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "Copy ClapTrap assignment operator called." << std::endl;
	this->_name = other._name;
	this->_hp = other._hp;
	this->_energy = other._energy;
	this->_attack = other._attack;

	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->_name << " has been destroyed by calling destructor." << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->_hp < 1)
		std::cout << "ClapTrap " << this->_name << " cannot attack, it is dead!" << std::endl;
	else
	{
		if (this->_energy < 1)
		{
			this->_energy = 0;
			std::cout << "ClapTrap " << this->_name << " is attempting to attack " << target << ", but it doesn't have enough energy!" << std::endl;
		}
		else
		{
			std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attack << " points of damage!" << std::endl;
			this->_energy -= 1;
		}

	}

}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hp == 0)
		std::cout << "ClapTrap " << this->_name << " cannot take any more damage, it is dead!" << std::endl;
	else
	{
		std::cout << "ClapTrap " << this->_name << " takes " << amount  << " points of damage!" << std::endl;
		if (this->_hp <= amount)
		{
			this->_hp = 0;
			std::cout << "ClapTrap " << this->_name << " is destroyed and died!" << std::endl;
		}
		else
			this->_hp -= amount;
	}
	
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energy < 1)
		std::cout << "ClapTrap " << this->_name << " is attempting to get repaired, but it doesn't have enough energy!" << std::endl;
	if (this->_hp < 1)
		std::cout << "ClapTrap " << this->_name << " cannot be repaired anymore, it is dead!" << std::endl;
	else if (this->_energy >= 1 && this->_hp >= 1)
	{
		std::cout << "ClapTrap " << this->_name << " is being repaired by " << amount  << " hp points!" << std::endl;
		this->_hp += amount;
		this->_energy -= 1;
	}

}

//////////////////////////////
//// getters and setters /////
//////////////////////////////
void	ClapTrap::setName(std::string name)
{
	this->_name = name;
}

std::string	ClapTrap::getName()
{
	return this->_name;
}

int		ClapTrap::getHp()
{
	return this->_hp;
}

int		ClapTrap::getEnergy()
{
	return this->_energy;
}

int		ClapTrap::getAttack()
{
	return this->_attack;
}