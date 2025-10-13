/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identifier.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:38:21 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/08 13:45:26 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Identifier.hpp"
#include "../inc/Macros.hpp"

/*
To work with dynamic_cast, there must be >=1 virtual function in the base class.
*/
Base::~Base() {}

/*
generate returns message with randomly created object.
std::rand() % 3 returns a random number between 0 and 2.
*/
Base*	generate(void)
{
	int randomNum = std::rand() % 3;
	switch (randomNum) {
		case 0:
			return (std::cout << "A created" << std::endl, new A);
		case 1:
			return (std::cout << "B created" << std::endl, new B);
		case 2:
			return (std::cout << "C created" << std::endl, new C);
		default:
			return (NULL);
	}
}

/* 
Identify from pointer.
The dynamic_cast<> from pointer is downcasting the base class.
In case of error,   it returns null pointer.
In case of success, it returns **pointer** to derived class from base class.
*/
void	identifyFromPtr(Base* base)
{
	if (dynamic_cast<A*>(base) != NULL)
		std::cout << "A identified from a " BB "pointer " RST "cast" << std::endl;
	else if (dynamic_cast<B*>(base) != NULL)
		std::cout << "B identified from a " BB "pointer " RST "cast" << std::endl;
	else if (dynamic_cast<C*>(base) != NULL)
		std::cout << "C identified from a " BB "pointer " RST "cast" << std::endl;
	else
		std::cout << BRERR "type identified from pointer cast" << std::endl;
}

/*
Identify from reference.
The dynamic_cast<> from reference is downcasting the base class.
In case of error,   it returns exception "std::bad_cast".
In case of success, it returns **reference** to derived class from base class
*/
void	identifyFromRef(Base& base)
{
	try {
		A& attemptA = dynamic_cast<A&>(base);
		std::cout << "A identified from a " BG "reference " RST "cast" << std::endl;
		(void)attemptA;
	}
	catch(const std::exception& e) {}
	
	try {
		B& attemptB = dynamic_cast<B&>(base);
		std::cout << "B identified from a " BG "reference " RST "cast" << std::endl;
		(void)attemptB;
	}
	catch( const std::exception& e ) {}
	
	try {
		C& attemptC = dynamic_cast<C&>(base);
		std::cout << "C identified from a " BG "reference " RST "cast" << std::endl;
		(void)attemptC;
	}
	catch( const std::exception& e ) {}
}
