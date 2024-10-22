/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/22 19:03:11 by psimcak          ###   ########.fr       */
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
# define BBLUE	"\033[1;34m"
# define RST	"\033[0m"

#define FRAC_BITS 8

class Fixed {

	private:
		int					_value;
		static const int	_fractionalBits = FRAC_BITS;

	public:
		Fixed( void );
		Fixed( const int );
		Fixed( const float );
		Fixed( Fixed const & );
		~Fixed();

		Fixed&	operator=( Fixed const & );

		int		getRawBits( void ) const;
		void	setRawBits( int const );
		float	toFloat( void ) const;
		int		toInt( void ) const;

};

std::ostream	&operator<<(std::ostream &, Fixed const &);

#endif

/* ***************************************************************  FIXED_HPP */