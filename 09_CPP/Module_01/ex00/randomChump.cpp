/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:27:13 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/09 16:52:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	Zombie::randomChump( std::string name ) {
	Zombie	basicZombie;

	basicZombie._name = name;
	basicZombie.announce(name);
	return ;
}

/************************************************************ randomChump.cpp */