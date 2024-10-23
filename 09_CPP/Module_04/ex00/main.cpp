/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 18:31:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <cstdlib>
#include <sstream>

int	main( void ) {
	// Constructor messages - one for animal, two (animal + dog) for dog, two (animal + cat) for cat
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << std::endl;			// output: Dog
	std::cout << i->getType() << std::endl;			// output: Cat
	std::cout << meta->getType() << std::endl;		// output: Animal
	i->makeSound(); 								// output the cat sound!
	j->makeSound();									// output the dog sound!
	meta->makeSound();								// output unspecified animal sound!

	// Destructor messages
	delete meta;
	delete j;
	delete i;

	// Demonstration of the wrong implementation
	const WrongAnimal*	wrong_meta = new WrongAnimal();
	const WrongAnimal*	wrong_i = new WrongCat();
	const Animal*		correct_meta = new Animal();
	const Animal*		correct_i = new Cat();

	std::cout << wrong_i->getType() << "\t\t\t" << correct_i->getType() << std::endl;
	std::cout << wrong_meta->getType() << "\t\t\t" << correct_meta->getType() << std::endl;
	std::cout << "-----------------------" << std::endl;
	wrong_i->makeSound();							// output: WrongAnimal sound
	std::cout << "VS" << std::endl;
	correct_i->makeSound();							// output: Cat sound
	std::cout << "-----------------------" << std::endl;
	wrong_meta->makeSound();						// output: WrongAnimal sound
	std::cout << "VS" << std::endl;
	correct_meta->makeSound();						// output: Animal sound
	std::cout << "-----------------------" << std::endl;

	delete wrong_meta; delete wrong_i; delete correct_meta; delete correct_i;

	return EXIT_SUCCESS;
}