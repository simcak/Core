/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:10:53 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 14:08:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::announce( void ) {
	std::cout << BB << this->_name << ": BraiiiiiiinnnzzzZ..." << RST << std::endl;
}

/** Constructor
 * _name(name) is an initialization list.
 * It initializes the _name attribute with the value of the name parameter.
*/
Zombie::Zombie( std::string name ) : _name(name) {
	std::cout << BG << _name << ": created" << RST << std::endl;
}

// Destructor
Zombie::~Zombie() {
	std::cout << BR << _name << ": destroyed" << RST << std::endl;
}

/***************************************************************** ZOMBIE_CPP */