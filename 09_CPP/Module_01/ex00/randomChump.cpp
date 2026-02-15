/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:27:13 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 13:55:19 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
   Stack Allocation:
 * When you create an object like Zombie basicZombie(name); inside this
   function, it is allocated on the stack.
 * The stack is a limited area of memory that automatically manages objects.
 * Once the function finishes, the object is destroyed, and its memory is freed.
 */
void	randomChump( std::string name ) {
	Zombie	basicZombie(name);

	basicZombie.announce();
	return ;
}

/************************************************************ randomChump.cpp */