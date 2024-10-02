/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:09:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 16:56:51 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

/* ****************** CONSTRUCTORS ****************** */
WrongAnimal::WrongAnimal() : type("WrongAnimal") {
	std::cout << BG << "Default WrongAnimal constructor called" << RST << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &src) {
	std::cout << BG << "WrongAnimal copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
WrongAnimal	&WrongAnimal::operator=(WrongAnimal const &src) {
	std::cout << "WrongAnimal assignation operator called" << std::endl;
	if (this != &src) {
		this->type = src.getType();
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
std::string	WrongAnimal::getType( void ) const {
	return type;
}

void	WrongAnimal::makeSound( void ) const {
	std::cout << BW << "Unspecified, wrong sound" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
WrongAnimal::~WrongAnimal() {
	std::cout << BR << "WrongAnimal destructor called" << RST << std::endl;
}
