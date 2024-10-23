/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:31:29 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 14:21:46 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <cstdlib>

#define HP		10
#define EP		10
#define AD		0
#define RP		5

// COLORS
#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
# define BBSL	"\033[1;34m" "************************************\n" "\033[0m"
# define BW		"\033[1;37m"
# define BO		"\033[1;33m"
#define RST		"\033[0m"

class ClapTrap {

	private:
		std::string	_name;
		int			_hitPoints;
		int			_energyPoints;
		int			_attackDamage;
		
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &clapTrap);

		ClapTrap	&operator=(const ClapTrap &);

		// Member functions
		void	attack(const std::string &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		// Getters and setters
		std::string	getName() const;
		void		setName(std::string name);
		int			getHitPoints() const;
		void		setHitPoints(int hitPoints);
		int			getEnergyPoints() const;
		void		setEnergyPoints(int energyPoints);
		int			getAttackDamage() const;
		void		setAttackDamage(int attackDamage);

		~ClapTrap();

};

// Operator overloads
std::ostream	&operator<<(std::ostream &, ClapTrap &);

#endif

/* ************************************************************  ClapTrap.hpp */