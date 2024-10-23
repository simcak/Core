/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 19:29:44 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ****************** CONSTRUCTORS ****************** */
Dog::Dog( void ) {
	std::cout << BG << "Dog dafault constructor called" << RST << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

Dog::Dog(Dog const &src) : Animal(src) {
	std::cout << BG << "Dog copy constructor called" << RST << std::endl;
	this->brain = new Brain(*src.getBrain());
}

/* ******************** OPERATORS ******************* */
Dog	&Dog::operator=(Dog const &src) {
	std::cout << BG << "Dog assignation operator called" << RST << std::endl;
	if (this != &src) {
		type = src.getType();
		*brain = *(src.getBrain());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	Dog::makeSound( void ) const {
	std::cout << BW << "Woof haf" << RST << std::endl;
}

Brain	*Dog::getBrain( void ) const {
	return this->brain;
}

/* ******************* DESTRUCTOR ******************* */
Dog::~Dog( void ) {
	delete this->brain;
	std::cout << BR << "Dog destructor called" << RST << std::endl;
}
