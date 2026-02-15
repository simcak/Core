/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/18 18:11:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/* ****************************** CONSTRUCTORS ****************************** */
// DEFAULT CONSTRUCTOR
Fixed::Fixed( void ) : _value(0) {}

// PARAMETRIZED CONSTRUCTOR
Fixed::Fixed( const int fp_value ) {
	_value = fp_value << _fractionalBits;
}

// PARAMETRIZED CONSTRUCTOR
Fixed::Fixed( const float fp_value ) {
	_value = roundf(fp_value * (1 << _fractionalBits));
}

// COPY CONSTRUCTOR
Fixed::Fixed( Fixed const &src ) {
	this->setRawBits(src.getRawBits());
}

// DESTRUCTOR
Fixed::~Fixed() {}

/* ********************** OPERATORS - MEMBER FUNCTIONS ********************** */
// COPY ASSIGNATION OPERATOR
Fixed&	Fixed::operator=( Fixed const &rhs ) {
	this->setRawBits(rhs.getRawBits());
	return *this;
}
// COMPARISON OPERATORS
// a > b in main is equivalent to a.operator>(b). So "this" = a & rhs = b
bool	Fixed::operator>( Fixed const &rhs ) const {
	return this->getRawBits() > rhs.getRawBits();
}

bool	Fixed::operator<( Fixed const &rhs ) const {
	return this->getRawBits() < rhs.getRawBits();
}

bool	Fixed::operator>=( Fixed const &rhs ) const {
	return this->getRawBits() >= rhs.getRawBits();
}

bool	Fixed::operator<=( Fixed const &rhs ) const {
	return this->getRawBits() <= rhs.getRawBits();
}

bool	Fixed::operator==( Fixed const &rhs ) const {
	return this->getRawBits() == rhs.getRawBits();
}

bool	Fixed::operator!=( Fixed const &rhs ) const {
	return this->getRawBits() != rhs.getRawBits();
}

// ARITHMETIC OPERATORS
Fixed	Fixed::operator+( Fixed const &rhs ) const {
	Fixed	result;

	result._value = this->getRawBits() + rhs.getRawBits();
	return result;
}

Fixed	Fixed::operator-( Fixed const &rhs ) const {
	Fixed	result;

	result._value = this->getRawBits() - rhs.getRawBits();
	return result;
}

// we need to rescale the result of the multiplication by the fractional bits
Fixed	Fixed::operator*( Fixed const &rhs ) const {
	Fixed	result;

	result._value = (this->getRawBits() * rhs.getRawBits()) >> _fractionalBits;
	return result;
}

Fixed	Fixed::operator/( Fixed const &rhs ) const {
	Fixed	result;

	result._value = (this->getRawBits() << _fractionalBits) / rhs.getRawBits();
	return result;
}

// INCREMENT AND DECREMENT OPERATORS - PREFIX AND POSTFIX
Fixed&	Fixed::operator++( void ) {
	this->_value++;
	return *this;
}

Fixed	Fixed::operator++( int ) {
	Fixed	tmp(*this);

	this->_value++;
	return tmp;
}

Fixed&	Fixed::operator--( void ) {
	this->_value--;
	return *this;
}

Fixed	Fixed::operator--( int ) {
	Fixed	tmp(*this);

	this->_value--;
	return tmp;
}

/* **************************** MEMBER FUNCTIONS **************************** */
Fixed const	&Fixed::min( Fixed const &a, Fixed const &b ) {
	return (a.getRawBits() < b.getRawBits()) ? a : b;
}

Fixed const	&Fixed::max( Fixed const &a, Fixed const &b ) {
	return (a.getRawBits() > b.getRawBits()) ? a : b;
}

Fixed&	Fixed::min( Fixed &a, Fixed &b ) {
	return (a.getRawBits() < b.getRawBits()) ? a : b;
}

Fixed&	Fixed::max( Fixed &a, Fixed &b ) {
	return (a.getRawBits() > b.getRawBits()) ? a : b;
}

int		Fixed::getRawBits( void ) const {
	return _value;
}

void	Fixed::setRawBits( int const raw ) {
	_value = raw;
}

float	Fixed::toFloat( void ) const {
	return ((float)_value / (float)(1 << _fractionalBits));
}

int		Fixed::toInt( void ) const {
	return _value >> _fractionalBits;
}

/* ******************** OPERATORS - NON MEMBER FUNCTIONS ******************** */
std::ostream	&operator<<(std::ostream &out, Fixed const &value) {
	if ((value.getRawBits() & ((1 << FRAC_BITS) - 1)) == 0) {
		out << value.toInt();
	} else {
		out << value.toFloat();
	}
	return out;
}

/* ***************************************************************  Fixed.cpp */