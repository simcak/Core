/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:33:15 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/08 11:35:53 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <iostream>
#include <stdint.h>	// uintptr_t

struct Data
{
	std::string	name;
	int			answer;
};

/**
 * UTILITY CLASS = static methods only
 * No need to create objects from it (functions are static).
 * Tharefore the constructors and destructor is private
 */
class Serializer
{
	private:
		/************************Orthodox Canonical Form***********************/
		Serializer();
		Serializer(const Serializer &);
		Serializer &operator=(const Serializer &);
		~Serializer();

	public:
		/****************************member function***************************/
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);

		/**********************************************************************/
};

#endif
