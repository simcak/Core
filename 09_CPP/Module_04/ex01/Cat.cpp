/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 19:29:51 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/* ****************** CONSTRUCTORS ****************** */
Cat::Cat( void ) {
	std::cout << BG << "Cat dafault constructor called" << RST << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(Cat const &src) : Animal(src) {
	std::cout << BG << "Cat copy constructor called" << RST << std::endl;
	this->brain = new Brain(*src.getBrain());
}

/* ******************** OPERATORS ******************* */
Cat	&Cat::operator=(Cat const &src) {
	std::cout << BG << "Cat assignation operator called" << RST << std::endl;
	if (this != &src) {
		type = src.getType();
		*brain = *(src.getBrain());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	Cat::makeSound( void ) const {
	std::cout << BW << "Meow mňau" << RST << std::endl;
}

Brain	*Cat::getBrain( void ) const {
	return this->brain;
}

/* ******************* DESTRUCTOR ******************* */
Cat::~Cat( void ) {
	delete this->brain;
	std::cout << BR << "Cat destructor called" << RST << std::endl;
}
