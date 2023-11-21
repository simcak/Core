#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	
	ClapTrap Crap("Crap");
	ScavTrap Scavanger("Scavanger");
	FragTrap Frankie("Frankie");

	std::cout << Crap.getName() << "'s status: " << Crap.getHp() << " HP | " << Crap.getEnergy() << " Energy" << std::endl;
	std::cout << Scavanger.getName() << "'s status: " << Scavanger.getHp() << " HP | " << Scavanger.getEnergy() << " Energy" << std::endl;
	std::cout << Frankie.getName() << "'s status: " << Frankie.getHp() << " HP | " << Frankie.getEnergy() << " Energy" << std::endl;


	Scavanger.attack("Crap");
	Crap.takeDamage(Scavanger.getAttack());
	Scavanger.guardGate();
	Crap.beRepaired(10);
	Frankie.highFivesGuys();
	Frankie.highFivesGuys();
	Frankie.highFivesGuys();


	std::cout << Crap.getName() << "'s status: " << Crap.getHp() << " HP | " << Crap.getEnergy() << " Energy" << std::endl;
	std::cout << Scavanger.getName() << "'s status: " << Scavanger.getHp() << " HP | " << Scavanger.getEnergy() << " Energy" << std::endl;
	std::cout << Frankie.getName() << "'s status: " << Frankie.getHp() << " HP | " << Frankie.getEnergy() << " Energy" << std::endl;

	return 0;
}