/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 19:48:37 by psimcak          ###   ########.fr       */
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
		virtual		~Dog();

		void		makeSound( void ) const;
		Brain		*getBrain( void ) const;

};

#endif
