/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:32:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 17:07:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::announce( void ) {
	std::cout << BB << "<" << _name << "_" << _id << "> Braiiiiiiinnnssss..." << RST << std::endl;
}

Zombie&	Zombie::setName( std::string name, int id ) {
	_name = name;
	_id = id;
	return *this;
}

// Default constructor
Zombie::Zombie( void ) : _name("zomzom"), _id(-1) {
	// std::cout << BG << "Zombie comrade has been created." << RST << std::endl;
}

// Destructor
Zombie::~Zombie( void ) {
	// std::cout << BR << _name << "_" << _id << " has been destroyed." << RST << std::endl;
}

/***************************************************************** Zombie.cpp */