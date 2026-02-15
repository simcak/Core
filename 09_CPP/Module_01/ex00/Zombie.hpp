/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:07:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/11 14:05:52 by psimcak          ###   ########.fr       */
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

// CLASS DEFINITIONS
class Zombie {

	public:
		Zombie( std::string name );
		void	announce( void );
		~Zombie();

	private:
		std::string	_name;

};

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

#endif /*********************************************************** ZOMBIE_HPP */