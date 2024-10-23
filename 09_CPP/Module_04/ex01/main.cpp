/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 20:06:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

#include <cstdlib>
# define ANIMALS	8

int	main( void )
{
	if (ANIMALS % 2)
		std::cerr << "Please provide an even number of animals" << std::endl;

	Animal	*tab[ANIMALS];
	Brain	*cat_brain;
	Brain	*dog_brain;

	std::cout << "----------------" << std::endl;
	Dog a;
	std::cout << "----------------" << std::endl;
	Dog b(a);
	std::cout << "----------------" << std::endl;

	for (int i = 0; i < ANIMALS; i++) {
		if (i < ANIMALS / 2) {
			tab[i] = new Dog();
			tab[i]->makeSound();
		}
		else {
			tab[i] = new Cat();
			tab[i]->makeSound();
		}
	}
	dog_brain = tab[0]->getBrain();
	cat_brain = tab[2]->getBrain();

	cat_brain->ideas[0] = dog_brain->ideas[0] = "Kibbles, let's GO !!";
	cat_brain->ideas[1] = dog_brain->ideas[1] = "I will rule them all";
	cat_brain->ideas[2] = dog_brain->ideas[2] = "I swear, it's not me for the slippers !";
	cat_brain->ideas[3] = dog_brain->ideas[3] = "OH, Master is putting his shoes on, maybe an outing ??";
	cat_brain->ideas[4] = dog_brain->ideas[4] = "...";

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "|" << tab[0]->getBrain()->ideas[0] << "|" << std::endl;
	*(tab[1]) = *(tab[0]);
	std::cout << "|" << tab[1]->getBrain()->ideas[1] << "|" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "|" << tab[2]->getBrain()->ideas[2] << "|" << std::endl;
	*(tab[3]) = *(tab[2]);
	std::cout << "|" << tab[3]->getBrain()->ideas[3] << "|" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	delete tab[0]; delete tab[1]; delete tab[2]; delete tab[3];
	std::cout << "===================================" << std::endl;

	const Animal*	j = new Dog();
	const Animal*	i = new Cat();
	delete j; delete i;

	std::cout << "===================================" << std::endl;
	// Deep copy tester - should output different ideas
	Dog dog1;
	dog1.getBrain()->ideas[0] = "mark it all good";

	Dog dog2(dog1); // Copy constructor
	dog2.getBrain()->ideas[0] = "outstanding project";

	std::cout << "Dog1 Brain Idea: " << dog1.getBrain()->ideas[0] << std::endl;
	std::cout << "Dog2 Brain Idea: " << dog2.getBrain()->ideas[0] << std::endl;

	return EXIT_SUCCESS;
}
