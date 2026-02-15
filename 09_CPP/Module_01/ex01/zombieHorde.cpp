/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:33:24 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 17:06:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	errMem( std::string funcName ) {
		std::cout << funcName << ": Cannot allocate memory." << std::endl;
		exit(ENOMEM);
}

Zombie*	zombieHorde( int N, std::string name ) {
	Zombie* zombies;

	zombies = new Zombie[N];
	if ( zombies == NULL )
		errMem("zombieHorde");
	
	for ( int i = 0; i < N; i++ ) {
		zombies[i].setName( name, i );
	}

	return zombies;
}


/************************************************************ zombieHorde.cpp */