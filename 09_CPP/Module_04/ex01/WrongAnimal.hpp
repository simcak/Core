/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:09:50 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 15:00:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>

// Colors
#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
#define BW		"\033[1;37m"
#define RST		"\033[0m"

/*
	Entiere point of this "wrong" implementation is by removing the virtual 
	keyword from the makeSound method in the base class (this class). 
	By doing so, the derived class (WrongCat) will not be able to override
	the makeSound method, and will instead use the base class's method.
*/
class WrongAnimal {

	protected:
		std::string		type;
	
	public:
		WrongAnimal();
		WrongAnimal(WrongAnimal const &);

		WrongAnimal	&operator=(WrongAnimal const &);

		std::string		getType( void ) const;
		void			makeSound( void ) const;

		virtual ~WrongAnimal();

};

#endif