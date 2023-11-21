#include "ClapTrap.hpp"

int main()
{
	ClapTrap Rubbish("Rubbish");
	ClapTrap Crap("Crap");

	std::cout << Rubbish.getName() << "'s status: " << Rubbish.getHp() << " HP | " << Rubbish.getEnergy() << " Energy" << std::endl;
	std::cout << Crap.getName() << "'s status: " << Crap.getHp() << " HP | " << Crap.getEnergy() << " Energy" << std::endl;


	for (int i = 0; i < 12; i++)
	{
		Rubbish.attack("Crap");
		Crap.takeDamage(Rubbish.getAttack());
	}

	
	std::cout << Rubbish.getName() << "'s status: " << Rubbish.getHp() << " HP | " << Rubbish.getEnergy() << " Energy" << std::endl;
	std::cout << Crap.getName() << "'s status: " << Crap.getHp() << " HP | " << Crap.getEnergy() << " Energy" << std::endl;

	Crap.beRepaired(3);
	std::cout << Crap.getName() << "'s status: " << Crap.getHp() << " HP | " << Crap.getEnergy() << " Energy" << std::endl;


	return 0;
}