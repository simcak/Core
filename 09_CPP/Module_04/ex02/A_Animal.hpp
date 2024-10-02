/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:06 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:28:24 by psimcak          ###   ########.fr       */
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

class A_Animal {

	protected:
		std::string		type;

	public:
		A_Animal();
		A_Animal(A_Animal const &);

		A_Animal	&operator=(A_Animal const &);

		virtual Brain			*getBrain( void ) const;
		virtual void			makeSound( void ) const = 0;
		std::string				getType( void ) const;

		virtual ~A_Animal();

};

#endif