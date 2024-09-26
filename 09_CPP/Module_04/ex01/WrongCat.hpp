/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:10:34 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/25 14:55:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

	public:
		WrongCat();
		WrongCat(WrongCat const &);

		WrongCat	&operator=(WrongCat const &);

		void	makeSound( void ) const;

		~WrongCat();

};

#endif