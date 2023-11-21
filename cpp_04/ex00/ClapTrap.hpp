#ifndef CLAP_TRAP_HPP
#define CLAP_TRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
	private:
				std::string		_name;
				unsigned int	_hp;
				unsigned int	_energy;
				unsigned int	_attack;

	public:
				/// constructors for create and copy, 
				/// assignment operator overload
				/// destructor
				/// aka OCCF part
				ClapTrap();
				ClapTrap(std::string name);
				ClapTrap(const ClapTrap& other);
				ClapTrap& operator=(const ClapTrap& other);
				~ClapTrap();

				/// subject methods ///
				void attack(const std::string& target);
				void takeDamage(unsigned int amount);
				void beRepaired(unsigned int amount);

				/// getters and setters
				void setName(std::string name);
				std::string getName();
				int getHp();
				int getEnergy();
				int getAttack();

};

#endif