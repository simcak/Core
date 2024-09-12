/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:13 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 15:03:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
	
	private:
		std::string	_name;
		Weapon		&_weapon;
		
	public:
		HumanA( std::string wName, Weapon &w );
		void		attack( void );
		~HumanA();
	
};

#endif

/* **************************************************************  HumanA.hpp */