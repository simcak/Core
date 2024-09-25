/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:06 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 14:58:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

// COLORS
#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
#define BW		"\033[1;37m"
#define RST		"\033[0m"

/*
	We create the base class by the orthodox canonical form (default constructor,
	copy constructor, assignation operator, destructor)
	We also create a virtual method makeSound, which will be overriden by the
	derived classes.
*/
class Animal {

	protected:
		std::string		type;

	public:
		Animal();
		Animal(Animal const &);

		Animal	&operator=(Animal const &);

		std::string		getType( void ) const;
		virtual void	makeSound( void ) const;

		virtual ~Animal();

};

#endif