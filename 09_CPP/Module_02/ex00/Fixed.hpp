/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:53:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/20 19:23:20 by psimcak          ###   ########.fr       */
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
		void	setRawBits( int const raw );

};

#endif

/* ***************************************************************  FIXED_HPP */