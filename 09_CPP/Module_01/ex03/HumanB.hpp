/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:12 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 15:22:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	
	private:
		std::string	_name;
		Weapon		*_weapon;
		
	public:
		HumanB( std::string name );
		void		setWeapon( Weapon &w );
		void		attack( void );
		~HumanB();
	
};

#endif

/* **************************************************************  HumanB.hpp */