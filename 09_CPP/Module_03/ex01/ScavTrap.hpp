/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/24 19:48:52 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

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