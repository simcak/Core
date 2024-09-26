/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 23:45:19 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

/* **************** SUPPORT FUNCTION **************** */
static bool	both_are_cats_or_dogs(Animal const &src1, Animal const &src2) {
	return ((src1.getType() == "Cat" || src1.getType() == "Dog") &&
			(src2.getType() == "Cat" || src2.getType() == "Dog"));
}

/* ****************** CONSTRACTORS ****************** */
Animal::Animal( void ) : type("Animal") {
	std::cout << BG << "Animal default constructor called" << RST << std::endl;
}

Animal::Animal( Animal const &src ) {
	std::cout << BG << "Animal copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
Animal	&Animal::operator=( Animal const &src ) {
	std::cout << BG << "Animal assignation constructor called" << RST << std::endl;
	if (both_are_cats_or_dogs(*this, src)) {
		*getBrain() = *src.getBrain();
	}
	if (this != &src) {
		this->type = src.type;
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
std::string	Animal::getType( void ) const {
	return type;
}

Brain	*Animal::getBrain( void ) const {
	return NULL;
}

void	Animal::makeSound( void ) const {
	std::cout << BW << "Unspecified sound" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
Animal::~Animal( void ) {
	std::cout << BR << "Animal destructor called" << RST <<std::endl;
}
