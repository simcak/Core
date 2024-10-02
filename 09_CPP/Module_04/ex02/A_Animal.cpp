/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:27:49 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"

/* ****************** CONSTRACTORS ****************** */
A_Animal::A_Animal( void ) : type("A_Animal") {
	std::cout << BG << "A_Animal default constructor called" << RST << std::endl;
}

A_Animal::A_Animal( A_Animal const &src ) {
	std::cout << BG << "A_Animal copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
A_Animal	&A_Animal::operator=( A_Animal const &src ) {
	std::cout << BG << "A_Animal assignation constructor called" << RST << std::endl;
	if (this != &src) {
		this->type = src.getType();
		*(this->getBrain()) = *(src.getBrain());
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
std::string	A_Animal::getType( void ) const {
	return type;
}

Brain	*A_Animal::getBrain( void ) const {
	return NULL;
}

void	A_Animal::makeSound( void ) const {
	std::cout << BW << "Unspecified sound" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
A_Animal::~A_Animal( void ) {
	std::cout << BR << "A_Animal destructor called" << RST <<std::endl;
}
