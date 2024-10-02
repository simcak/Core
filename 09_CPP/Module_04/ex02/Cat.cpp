/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:27:23 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/* ****************** CONSTRUCTORS ****************** */
Cat::Cat( void ) {
	std::cout << BG << "Cat dafault constructor called" << RST << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(Cat const &src) : A_Animal(src) {
	std::cout << BG << "Cat copy constructor called" << RST << std::endl;
	this->brain = new Brain();
	*this = src;
}

/* ******************** OPERATORS ******************* */
Cat	&Cat::operator=(Cat const &src) {
	std::cout << "Cat assignation operator called" << std::endl;
	if (this != &src) {
		this->type = src.getType();
		*(this->brain) = *(src.getBrain());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	Cat::makeSound( void ) const {
	std::cout << BW << "Meow mňau" << RST << std::endl;
}

Brain	*Cat::getBrain( void ) const {
	return (this->brain);
}

/* ******************* DESTRUCTOR ******************* */
Cat::~Cat( void ) {
	std::cout << BR << "Cat destructor called" << RST << std::endl;
	delete this->brain;
}
