#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap
{
	public:
				/// constructors for create and copy, 
				/// assignment operator overload
				/// destructor
				/// aka OCCF part
				FragTrap();
				FragTrap(std::string name);
				FragTrap(const FragTrap& other);
				FragTrap& operator=(const FragTrap& other);
				~FragTrap();

				/// subject method
				void highFivesGuys(void);
				void attack(const std::string& target);
};

#endif