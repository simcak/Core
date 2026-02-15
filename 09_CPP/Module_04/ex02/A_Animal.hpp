/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:06 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 19:58:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_ANIMAL_HPP
# define A_ANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

// COLORS
#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
#define BW		"\033[1;37m"
#define RST		"\033[0m"

/**
 * in this exercise we have added the Pure Virtual Function makeSound() to the
 * class by "=0". This makes the class an abstract class and we cannot create
 * objects of this class. We can only create objects of the derived classes.
 */
class A_Animal {

	protected:
		std::string		type;

	public:
		A_Animal();
		A_Animal(A_Animal const &);
		A_Animal	&operator=(A_Animal const &);
		virtual ~A_Animal();

		virtual Brain			*getBrain( void ) const;
		virtual void			makeSound( void ) const = 0;
		std::string				getType( void ) const;

};

#endif