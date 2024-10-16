/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/18 20:41:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cstdlib>

class Fixed
{

	private:
		int					_value;
		static const int	_fractionalBits = 8;

	public:
		Fixed( void );
		Fixed( Fixed const & );
		Fixed&	operator=( Fixed const & );
		~Fixed();

		int		getRawBits( void ) const;
		void	setRawBits( int const );

};

#endif

/* ***************************************************************  FIXED_HPP */