/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:28:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "A_Animal.hpp"

class Dog : public A_Animal {

	private:
		Brain	*brain;

	public:
		Dog();
		Dog(Dog const &);

		Dog	&operator=(Dog const &);

		void		makeSound( void ) const;
		Brain		*getBrain( void ) const;

		virtual		~Dog();

};

#endif
