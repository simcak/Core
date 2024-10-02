/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:13:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ****************** CONSTRUCTORS ****************** */
Dog::Dog( void ) {
	std::cout << BG << "Dog dafault constructor called" << RST << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

// here we delete the Animal copy constructor call. 
Dog::Dog(Dog const &src) {
	std::cout << BG << "Dog copy constructor called" << RST << std::endl;
	this->brain = new Brain();
	*this = src;
}

/* ******************** OPERATORS ******************* */
Dog	&Dog::operator=(Dog const &src) {
	std::cout << BG << "Dog assignation operator called" << RST << std::endl;
	if (this != &src) {
		this->type = src.getType();
		*(this->brain) = *(src.getBrain());
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
	std::cout << BR << "Dog destructor called" << RST << std::endl;
	delete this->brain;
}
