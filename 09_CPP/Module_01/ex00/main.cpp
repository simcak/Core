/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:28:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 14:01:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"


/**
Stack Allocation:
 *	When you create an object like Zombie basicZombie(name); inside a function
	(e.g., randomChump), it is allocated on the stack. The stack is a limited
	area of memory that automatically manages objects. Once the function
	finishes, the object is destroyed, and its memory is freed.

Heap Allocation:
 *	When you create an object like Zombie *zombie = new Zombie(name); 
	(in newZombie), it is allocated on the heap.
	The heap is a larger, manually managed area of memory.
	Objects created on the heap remain in memory until you explicitly delete
	them with delete. If you don't delete them, you get a memory leak.

Stack:
- Fast, automatic memory management (object is deleted at the end of the func.)
Heap:
- Slower, manual management (you need to use delete)

The stack/heop allocation is a core reason for this exercise.
 */
int		main( void ) {
	randomChump("StackZombie");
	Zombie *zombie = newZombie("HeapZombie");

	zombie->announce();
	delete zombie;
	return EXIT_SUCCESS;
}

/******************************************************************* main.cpp */