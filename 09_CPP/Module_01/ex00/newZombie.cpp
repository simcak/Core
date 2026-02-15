/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:25:03 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 14:20:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
   Heap Allocation:
 * When you create an object like in here, it is allocated on the heap.
 * The heap is a larger, manually managed area of memory.
 * Objects created on the heap remain in memory until you explicitly delete
   them with delete. If you don't delete them, you get a memory leak.
*/
Zombie* newZombie( std::string name ) {
	Zombie	*newZombie = new Zombie(name);
	return newZombie;
}

/************************************************************** newZombie.cpp */