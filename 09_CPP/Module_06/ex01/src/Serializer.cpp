/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:36:47 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/07 14:47:55 by psimcak          ###   ########.fr       */
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
uintptr_t	Serializer::serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serializer::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}
