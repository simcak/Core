/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:30:04 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 16:20:30 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::debug( void ) {
	std::cout << G << DEBUG_MSG << RST << std::endl;
}

void	Harl::info( void ) {
	std::cout << B << INFO_MSG << RST << std::endl;
}

void	Harl::warning( void ) {
	std::cout << Y << WARNING_MSG << RST << std::endl;
}

void	Harl::error( void ) {
	std::cout << R << ERROR_MSG << RST << std::endl;
}

void	Harl::complain( std::string level ) {
	std::string	level_list[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };

	for (int i = 0 ; i < 4 ; i++) {
		if (level == level_list[i]) {
			(this->*_levels[i].function)();
			return ;
		}
	}
	std::cout << "I don't know what to say..." << std::endl;
}

// Constructor
Harl::Harl() {
	_levels[DEBUG].function = &Harl::debug;
	_levels[INFO].function = &Harl::info;
	_levels[WARNING].function = &Harl::warning;
	_levels[ERROR].function = &Harl::error;
}

// Destructor
Harl::~Harl() {}

/* ****************************************************************  Harl.cpp */