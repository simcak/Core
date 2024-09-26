/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 17:25:53 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ****************** CONSTRUCTORS ****************** */
Dog::Dog() {
	std::cout << BG << "Dog dafault constructor called" << RST << std::endl;
	this->type = "Dog";
}

Dog::Dog(Dog const &src) : Animal(src) {
	std::cout << BG << "Dog copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
Dog	&Dog::operator=(Dog const &src) {
	std::cout << "Dog assignation operator called" << std::endl;
	if (this != &src) {
		this->type = src.getType();
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	Dog::makeSound( void ) const {
	std::cout << BW << "Woof haf" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
Dog::~Dog() {
	std::cout << BR << "Dog destructor called" << RST << std::endl;
}
