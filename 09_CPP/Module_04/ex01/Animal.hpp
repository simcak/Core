/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:06 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 23:22:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

// COLORS
#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
#define BW		"\033[1;37m"
#define RST		"\033[0m"

class Animal {

	protected:
		std::string		type;

	public:
		Animal();
		Animal(Animal const &);

		Animal	&operator=(Animal const &);

		virtual std::string		getType( void ) const;
		virtual Brain			*getBrain( void ) const;
		virtual void			makeSound( void ) const;

		virtual ~Animal();

};

#endif