/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:23:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 17:27:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "A_Animal.hpp"

class Cat : public A_Animal {

	private:
		Brain	*brain;

	public:
		Cat();
		Cat(Cat const &);

		Cat	&operator=(Cat const &);

		void		makeSound( void ) const;
		Brain		*getBrain( void ) const;

		virtual		~Cat();

};

#endif
