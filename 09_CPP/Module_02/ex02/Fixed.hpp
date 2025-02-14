/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/22 20:02:23 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

# define BWHITE	"\033[1;37m"
# define BRED	"\033[1;31m"
# define BGREEN	"\033[1;32m"
# define BB		"\033[1;34m"
# define RST	"\033[0m"
# define BBS	"\033[1;34m" << "* " << RST

#define FRAC_BITS 8

class Fixed {

	private:
		int					_value;
		static const int	_fractionalBits = FRAC_BITS;

	public:
		// CONSTRUCTORS AND DESTRUCTOR
		Fixed( void );
		Fixed( const int );
		Fixed( const float );
		Fixed( Fixed const & );
		~Fixed();

		// COMPARISON OPERATORS
		Fixed&	operator=( Fixed const & );
		bool	operator>( Fixed const & ) const;
		bool	operator<( Fixed const & ) const;
		bool	operator>=( Fixed const & ) const;
		bool	operator<=( Fixed const & ) const;
		bool	operator==( Fixed const & ) const;
		bool	operator!=( Fixed const & ) const;

		// ARITHMETIC OPERATORS
		Fixed	operator+( Fixed const &) const;
		Fixed	operator-( Fixed const &) const;
		Fixed	operator*( Fixed const &) const;
		Fixed	operator/( Fixed const &) const;

		// INCREMENT AND DECREMENT OPERATORS - PREFIX AND POSTFIX
		Fixed&	operator++( void );
		Fixed	operator++( int );
		Fixed&	operator--( void );
		Fixed	operator--( int );

		// MEMBER FUNCTIONS
		// static functions are suitable for utility functions that don't need
		// to operate on a specific object’s state.
		static Fixed const	&min( Fixed const &, Fixed const & );
		static Fixed const	&max( Fixed const &, Fixed const & );
		static Fixed&		min( Fixed &, Fixed & );
		static Fixed&		max( Fixed &, Fixed & );
		int					getRawBits( void ) const;
		void				setRawBits( int const );
		float				toFloat( void ) const;
		int					toInt( void ) const;

};

std::ostream	&operator<<(std::ostream &, Fixed const &);

#endif

/* ***************************************************************  FIXED_HPP */