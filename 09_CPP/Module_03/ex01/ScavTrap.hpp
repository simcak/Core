/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 20:24:21 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

/* ScavTrap is a derived class of the base class ClapTrap
	- All the public members of ClapTrap become public in ScavTrap
	- Private members of ClapTrap are not directly accessible by ScavTrap,
	but ScavTrap can access them through any public
*/
class ScavTrap : public ClapTrap {

	public:
		ScavTrap();
		ScavTrap( const std::string &name );
		ScavTrap( ScavTrap &scavTrap );

		// Member functions
		void	attack( std::string const &target );
		void	guardGate( void );
		
		~ScavTrap();

};

#endif