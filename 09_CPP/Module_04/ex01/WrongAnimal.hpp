/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:09:50 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 18:33:30 by psimcak          ###   ########.fr       */
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

class WrongAnimal {

	protected:
		std::string		type;
	
	public:
		WrongAnimal();
		WrongAnimal(WrongAnimal const &);
		WrongAnimal	&operator=(WrongAnimal const &);
		virtual ~WrongAnimal();

		std::string		getType( void ) const;
		void			makeSound( void ) const;

};

#endif