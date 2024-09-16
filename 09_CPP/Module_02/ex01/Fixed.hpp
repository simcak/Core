/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/16 19:46:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed {

	private:
		int					_value;
		static const int	_fractionalBits = 8;

	public:
		Fixed( void );
		Fixed( const int );
		Fixed( const float );
		Fixed( Fixed const & );
		Fixed&	operator=( Fixed const & );
		~Fixed();

		int		getRawBits( void ) const;
		void	setRawBits( int const );
		float	toFloat( void ) const;
		int		toInt( void ) const;

};
#endif

/* ***************************************************************  FIXED_HPP */