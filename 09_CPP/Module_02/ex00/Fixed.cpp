/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/16 18:57:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int		Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return _value;
}

void	Fixed::setRawBits( int const raw ) {
	_value = raw;
}

/**
 * The copy constructor creates a new object as a copy of an existing one,
 * ensuring that any dynamically allocated resources are copied correctly.
 */
Fixed::Fixed( Fixed const &src_cls ) {
	std::cout << "Copy constructor called" << std::endl;
	this->setRawBits(src_cls.getRawBits());
}

/**
 * The copy assignment operator handles assigning the contents of one object to
 * an already existing object, managing the old resources and performing a deep
 * copy to avoid problems like memory leaks.
 */
Fixed&	Fixed::operator=( Fixed const &rhs ) {
	std::cout << "Copy assignation operator called" << std::endl;
	this->setRawBits(rhs.getRawBits());
	return *this;
}

// Constructor
Fixed::Fixed( void ) : _value(0) {
	std::cout << "Default constructor called" << std::endl;
}

// Destructor
Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

/* ***************************************************************  Fixed.cpp */