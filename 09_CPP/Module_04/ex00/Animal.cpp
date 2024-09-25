/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:09 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 15:00:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

/* ****************** CONSTRACTORS ****************** */
Animal::Animal() : type("Animal") {
	std::cout << BG << "Animal default constructor called" << RST << std::endl;
}

Animal::Animal(Animal const &src) {
	std::cout << BG << "Animal copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
Animal	&Animal::operator=(Animal const &src) {
	std::cout << "Animal assignation constructor called" << std::endl;
	if (this != &src) {
		// Copy data from src to this object
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
std::string	Animal::getType( void ) const {
	return type;
}

void	Animal::makeSound( void ) const {
	std::cout << BW << "Unspecified sound" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
Animal::~Animal() {
	std::cout << BR << "Animal destructor called" << RST <<std::endl;
}
