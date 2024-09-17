/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/17 21:34:27 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// DEFAULT CONSTRUCTOR
Fixed::Fixed( void ) : _value(0) {
	std::cout << "Default constructor called" << std::endl;
}

/** PARAMETRIZED CONSTRUCTOR
 * It converts it to the corresponding fixed-point value. The fractional bits
 * value isinitialized to 8
 * 
 * const is used here tharefore the fp_value will not be changed.
 */
Fixed::Fixed( const int fp_value ) {
	std::cout << "Int constructor called" << std::endl;
	_value = fp_value << _fractionalBits;
}

/**
 * It converts it to the corresponding fixed-point value. The fractional bits
 * value is initialized to 8
 */
Fixed::Fixed( const float fp_value ) {
	std::cout << "Float constructor called" << std::endl;
	_value = roundf(fp_value * (1 << _fractionalBits));
}

/** COPY CONSTRUCTOR
 * The copy constructor creates a new object as a copy of an existing one,
 * ensuring that any dynamically allocated resources are copied correctly.
 */
Fixed::Fixed( Fixed const &src ) {
	std::cout << "Copy constructor called" << std::endl;
	this->setRawBits(src.getRawBits());
}

// DESTRUCTOR
Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

/** COPY ASSIGNATION OPERATOR
 * The copy assignment operator handles assigning the contents of one object to
 * an already existing object, managing the old resources and performing a deep
 * copy to avoid problems like memory leaks.
 */
Fixed&	Fixed::operator=( Fixed const &rhs ) {
	std::cout << "Copy assignation operator called" << std::endl;
	this->setRawBits(rhs.getRawBits());
	return *this;
}

// MEMBER FUNCTION
int		Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return _value;
}

// MEMBER FUNCTION
void	Fixed::setRawBits( int const raw ) {
	_value = raw;
}

float	Fixed::toFloat( void ) const {
	return ((float)_value / (float)(1 << _fractionalBits));
}

int		Fixed::toInt( void ) const {
	return _value >> _fractionalBits;
}

std::ostream	&operator<<(std::ostream &out, Fixed const &value) {
	out << value.toFloat();
	return out;
}

/* RIGHT and LEFT shift operators
- Left Shift (<<): Multiplies the number by 2^n. Each shift left makes the
  number larger.
	Example: If you have 5 (00000101 in binary) and shift it left by 2 (5 << 2),
	it becomes 20 (00010100). The binary digits are shifted to the left, adding
	zeros at the right end.

- Right Shift (>>): Divides the number by 2^n. Each shift right makes the number
  smaller, effectively "chopping off" the less significant bits.
	Example: If you have 20 (00010100 in binary) and shift it right by 2
	(20 >> 2), it becomes 5 (00000101). The binary digits are shifted to the
	right, dropping the bits at the end.
*/
/* ***************************************************************  Fixed.cpp */