/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:10:37 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 16:57:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

/* ****************** CONSTRUCTORS ****************** */
WrongCat::WrongCat() {
	this->type = "WrongCat";
	std::cout << BG << "WrongCat default constructor called" << RST << std::endl;
}

WrongCat::WrongCat(WrongCat const &src) {
	std::cout << BG << "WrongCat copy constructor called" << RST << std::endl;
	*this = src;
}

/* ******************** OPERATORS ******************* */
WrongCat	&WrongCat::operator=(WrongCat const &src) {
	std::cout << "WrongCat assignation operator called" << std::endl;
	if (this != &src) {
		this->type = src.getType();
	}
	return *this;
}

/* **************** MEMBER FUNCTIONS **************** */
void	WrongCat::makeSound( void ) const {
	std::cout << BW << "Meooow" << RST << std::endl;
}

/* ******************* DESTRUCTOR ******************* */
WrongCat::~WrongCat() {
	std::cout << BR << "WrongCat destructor called" << RST << std::endl;
}
