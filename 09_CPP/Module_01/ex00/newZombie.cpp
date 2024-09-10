/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:25:03 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/09 16:45:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* Zombie::newZombie( std::string name ) {
	Zombie *newZombie = new Zombie();
	return newZombie;
}

/************************************************************** newZombie.cpp */