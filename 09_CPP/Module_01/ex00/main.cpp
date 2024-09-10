/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:28:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/09 16:54:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int		main( void ) {
	Zombie *zombie = new Zombie();

	zombie->newZombie("Franta");
	zombie->randomChump("Jozko");
	delete zombie;
	return 0;
}

/******************************************************************* main.cpp */