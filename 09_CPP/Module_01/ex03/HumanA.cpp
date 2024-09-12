/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 16:04:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

void	HumanA::attack( void )
{
	std::cout << BY << _name << " attacks with his " << _weapon.getType() << RST << std::endl;
}

HumanA::HumanA(std::string wName, Weapon &w) : _name(wName), _weapon(w)
{
	std::cout << BW << _name << BG << " rises" << RST << std::endl;
}

HumanA::~HumanA()
{
	std::cout << BW << _name << BR << " fell" << RST << std::endl;
}

/* **************************************************************  HumanA.cpp */