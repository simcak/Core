/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:30:03 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 16:36:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

// Libraries
#include <iostream>
#include <string>

// Colors
#define BW			"\033[1;37m"
#define G			"\033[0;32m"
#define B			"\033[0;34m"
#define Y			"\033[0;33m"
#define R			"\033[0;31m"
#define RST			"\033[0m"

// Levels
#define DEBUG		0
#define INFO		1
#define WARNING		2
#define ERROR		3

// Messages
#define DEBUG_MSG	"I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger.\nI really do!"
#define INFO_MSG	"I cannot believe adding extra bacon costs more money.\nYou didn't putenough bacon in my burger! If you did, I wouldn't be asking for more!"
#define WARNING_MSG	"I think I deserve to have some extra bacon for free.\nI've been coming for years whereas you started working here since last month."
#define ERROR_MSG	"This is unacceptable! I want to speak to the manager now."

// Class definition
class Harl {

	private:

		typedef struct	Complain_s {
			void		( Harl::*function )( void );
		}				Complain_t;

		Complain_t		_levels[4];
		void			debug( void );
		void			info( void );
		void			warning( void );
		void			error( void );

	public:
		Harl( void );
		void	complain( std::string level );
		~Harl( void );

};

#endif

/* ****************************************************************  Harl.hpp */