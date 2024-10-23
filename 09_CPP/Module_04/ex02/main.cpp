/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:52:54 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 20:08:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

#include <cstdlib>

int main()
{
	// Next line will not compile because A_Animal is an abstract class
	// A_Animal* animal = new A_Animal();

	// This is ok - we can create objects of the derived classes
	A_Animal* arr[2];

	arr[0] = new Dog();
	arr[1] = new Cat();

	delete arr[0];
	delete arr[1];
	std::cout << BG << "Oll Korrekt = OK" << RST << std::endl;

	return EXIT_SUCCESS;
}
