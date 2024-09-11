/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:23:43 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 16:56:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>																// std::cout, std::endl

// COLOR DEFINITIONS
# define R			"\033[31m"													// Red
# define G			"\033[32m"													// Green
# define B			"\033[34m"													// Blue
# define Y			"\033[33m"													// Yellow
# define BR			"\033[1m\033[31m"											// Bold Red
# define BG			"\033[1m\033[32m"											// Bold Green
# define BB			"\033[1m\033[34m"											// Bold Blue
# define BY			"\033[1m\033[33m"											// Bold Yellow
# define RST		"\033[0m"													// Reset

# define ENOMEM					12												/* Cannot allocate memory */

// CLASS DEFINITIONS
class Zombie {
	
	public:
		Zombie();
		void	announce( void );
		Zombie&	setName( std::string name, int id );
		~Zombie();

	private:
		std::string	_name;
		int			_id;
};

// FUNCTION PROTOTYPES
Zombie*	zombieHorde( int N, std::string name );

#endif /*********************************************************** ZOMBIE_HPP */