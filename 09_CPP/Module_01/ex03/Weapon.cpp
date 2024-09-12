/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:07 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/12 15:58:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

/**
 * we use the CONST keywords to make sure that the function does not modify the
 * object it is called on. This is a good practice to follow, as it makes the
 * code easier to understand and maintain.
 * 
 * reference symbol (&) is used to pass the object by reference, which means
 * that the function will be able to modify the object it is called on. Without
 * it, the function would only receive a copy of the object, and any changes
 * made to it would not be reflected in the original object.
 */
const std::string	&Weapon::getType( void ) const
{
	return _type;
}

void	Weapon::setType( const std::string &type )
{
	_type = type;
}

Weapon::Weapon( std::string wType ) : _type(wType)
{
	std::cout << BW << _type << BG << " is created" << RST << std::endl;
}

Weapon::~Weapon()
{
	std::cout << BW << _type << BR << " is destroyed" << RST << std::endl;
}

/* **************************************************************  Weapon.cpp */