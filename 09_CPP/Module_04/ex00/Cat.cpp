/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:52 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 17:23:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/* ****************** CONSTRUCTORS ****************** */
Cat::Cat() {
	std::cout << BG << "Cat dafault constructor called" << RST << std::endl;
	this->type = "Cat";
}

Cat::Cat(Cat const &src) : Animal(src) {
	std::cout << BG << "Cat copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
Cat	&Cat::operator=(Cat const &src) {
	std::cout << "Cat assignation operator called" << std::endl;
	if (this != &src) {
		this->type = src.getType();
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	Cat::makeSound( void ) const {
	std::cout << BW << "Meow mňau" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
Cat::~Cat() {
	std::cout << BR << "Cat destructor called" << RST << std::endl;
}
