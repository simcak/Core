/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:07:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/09 16:30:12 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>																// std::cout, std::endl

// COLOR DEFINITIONS
#define R			"\033[31m"
#define G			"\033[32m"
#define B			"\033[34m"
#define Y			"\033[33m"
#define BR			"\033[1m\033[31m"
#define BG			"\033[1m\033[32m"
#define BB			"\033[1m\033[34m"
#define BY			"\033[1m\033[33m"
#define RST			"\033[0m"

// CLASS DEFINITIONS
class Zombie {

	public:
		Zombie();
		Zombie*	newZombie( std::string name );
		void	randomChump( std::string name );
		void	announce( std::string name );
		~Zombie();

	private:
		std::string	_name;

};

#endif /*********************************************************** ZOMBIE_HPP */