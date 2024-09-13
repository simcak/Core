/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:30:04 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 17:04:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::debug( void ) {
	std::cout << G << "[  DEBUG  ]" << RST << std::endl;
	std::cout << G << DEBUG_MSG << RST << std::endl;
}

void	Harl::info( void ) {
	std::cout << B << "[  INFO  ]" << RST << std::endl;
	std::cout << B << INFO_MSG << RST << std::endl;
}

void	Harl::warning( void ) {
	std::cout << Y << "[  WARNING  ]" << RST << std::endl;
	std::cout << Y << WARNING_MSG << RST << std::endl;
}

void	Harl::error( void ) {
	std::cout << R << "[  ERROR  ]" << RST << std::endl;
	std::cout << R << ERROR_MSG << RST << std::endl;
}

void	Harl::complain( std::string level ) {
	std::string	level_list[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	int			i;

	for (i = 0 ; i < 4 ; i++) {
		if (level == level_list[i]) {
			break ;
		}
	}
	switch (i)
	{
		case DEBUG:
			(this->*_levels[DEBUG].function)();
		case INFO:
			(this->*_levels[INFO].function)();
		case WARNING:
			(this->*_levels[WARNING].function)();
		case ERROR:
			(this->*_levels[ERROR].function)();
				break;
	
		default:
			std::cout << DEFAULT_MSG << std::endl;
			break;
	}
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