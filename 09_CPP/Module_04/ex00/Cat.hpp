/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 17:24:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

/*
	In C++, once a member function is declared as virtual in the base class, it
	remains virtual in all derived classes, even if you don't explicitly declare
	it as virtual in the derived classes.
	If we declare it than it is just for better readability.
	In C++11 and later, we can use the 'override' keyword to be explicit.
*/
class Cat : public Animal {

	public:
		Cat();
		Cat(Cat const &);

		Cat	&operator=(Cat const &);

		void		makeSound( void ) const;

		~Cat();

};

#endif
