/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:29:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/18 20:39:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <cstdlib>

void	tester(Zombie* zombies, int N) {
	for ( int i = 0; i < N; i++ ) {
		zombies[i].announce();
	}
}

int	main( void ) {
	int		N = 5;
	Zombie*	zombies = zombieHorde( N, "Zombie" );

	tester(zombies, N);

	delete [] zombies;
	return EXIT_SUCCESS;
}

/******************************************************************* main.cpp */