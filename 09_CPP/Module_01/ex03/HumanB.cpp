/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 16:04:51 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

void	HumanB::setWeapon( Weapon &w )
{	
	_weapon = &w;
}

void	HumanB::attack( void )
{
	if (_weapon != NULL)
		std::cout << BY << _name << " attacks with his " << _weapon->getType() << RST << std::endl;
}

HumanB::HumanB( std::string name ) : _name(name), _weapon(NULL)
{
	std::cout << BW << _name << BG <<" rises" << RST << std::endl;
}

HumanB::~HumanB()
{
	std::cout << BW << _name << BR << " fell" << RST << std::endl;
}

/* **************************************************************  HumanB.cpp */