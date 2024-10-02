/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:52:54 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:29:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	A_Animal* arr[2];

	arr[0] = new Dog();
	arr[1] = new Cat();

	delete arr[0];
	delete arr[1];
	std::cout << "Pass" << std::endl;

	return EXIT_SUCCESS;
}
