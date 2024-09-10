/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:10:53 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/09 16:46:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::announce( std::string name ) {
	std::cout << BB << name << ": BraiiiiiiinnnzzzZ..." << RST << std::endl;
}

Zombie::Zombie() {
	_name = "unknownZombie";
}

Zombie::~Zombie() {
	std::cout << BR << _name << ": destroyed" << RST << std::endl;
}

/***************************************************************** ZOMBIE_CPP */