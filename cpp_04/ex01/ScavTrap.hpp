#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
	public:
				/// constructors for create and copy, 
				/// assignment operator overload
				/// destructor
				/// aka OCCF part
				ScavTrap();
				ScavTrap(std::string name);
				ScavTrap(const ScavTrap& other);
				ScavTrap& operator=(const ScavTrap& other);
				~ScavTrap();

				/// subject method
				void guardGate();
				void attack(const std::string& target);
};

#endif