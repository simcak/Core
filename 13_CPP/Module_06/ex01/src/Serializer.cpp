/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:36:47 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/07 18:44:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"

/****************************Orthodox Canonical Form***************************/
Serializer::Serializer() {}

Serializer::Serializer(const Serializer &copy) {
	*this = copy;
}

Serializer	&Serializer::operator=(const Serializer &src) {
	(void)src;
	return (*this);
}

Serializer::~Serializer() {}

/*******************************member functions*******************************/
// takes adress (e.g. 0x7ffee3a0) and converts it to number <uintptr_t>
uintptr_t	Serializer::serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

// takse serialized number (e.g. hex-num: 7ffee3a0) and converts it back to
// original data
Data*	Serializer::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}
