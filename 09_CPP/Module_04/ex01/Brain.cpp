/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:15:27 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/23 19:46:06 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/* ****************** CONSTRACTORS ****************** */
Brain::Brain( void ) : ideas() {
	std::cout << BG << "Brain default constructor called" << RST << std::endl;
}

Brain::Brain(Brain const &src) {
	std::cout << BG << "Brain copy constructor called" << RST << std::endl;
	for (unsigned int i = 0 ; i < 100 ; ++i)
		ideas[i] = src.ideas[i];
}

/* ******************** OPERATORS ******************* */
Brain	&Brain::operator=(Brain const &src) {
	std::cout << BG << "Brain assignation constructor called" << RST << std::endl;
	if (this != &src)
		for (unsigned int i = 0 ; i < 100 ; ++i)
			this->ideas[i] = src.ideas[i];
	return *this;
}

/* ******************* DESTRUCTOR ******************* */
Brain::~Brain( void ) {
	std::cout << BR << "Brain destructor called" << RST <<std::endl;
}
