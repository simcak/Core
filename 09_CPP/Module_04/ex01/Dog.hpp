/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 23:20:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {

	private:
		Brain	*brain;

	public:
		Dog();
		Dog(Dog const &);

		Dog	&operator=(Dog const &);

		void		makeSound( void ) const;
		Brain		*getBrain( void ) const;

		~Dog();

};

#endif
