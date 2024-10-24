/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:58:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/18 20:43:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {

	public:
		FragTrap();
		FragTrap( const std::string &name );
		FragTrap( FragTrap &fragTrap );

		FragTrap	&operator=( FragTrap & );

		void	attack( std::string const &target );
		void	highFivesGuys( void );

		~FragTrap();

};


#endif

/* ************************************************************  FragTrap.hpp */