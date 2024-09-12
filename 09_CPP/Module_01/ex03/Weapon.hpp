/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:15 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 16:04:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <stdlib.h>
#include <string>
#include <iostream>

// COLOR CODES
#define BW			"\033[1;37m"
#define BR			"\033[1;31m"
#define BG			"\033[1;32m"
#define BY			"\033[1;33m"
#define RST			"\033[0m"

class Weapon
{
	private:
		std::string			_type;
	public:
		Weapon( std::string wType );
		const std::string	&getType() const;
		void				setType(const std::string &type);
		~Weapon();
};

#endif

/* *************************************************************** Weapon.hpp */