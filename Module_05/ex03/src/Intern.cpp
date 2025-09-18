/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:55:09 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 16:42:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Intern.hpp"

/***************************Orthodox Canonical Form****************************/
Intern::Intern() {}

Intern::Intern(const Intern &other) {
	*this = other;
}

Intern &Intern::operator=(const Intern &src) {
	(void)src;
	return *this;
}

Intern::~Intern() {
	std::cout << BR "Intern destructor called" RST << std::endl;
}

/*******************************member functions*******************************/
AForm *Intern::makeForm(std::string name, std::string target) {
	const std::string formNames[3] = {
		"shrubbery", "robotomy", "presidential"
	};
	AForm *forms[3] = {
		new ShrubberyCreationForm(target), new RobotomyRequestForm(target),
		new PresidentialPardonForm(target)
	};

	for (int i = 0; i < 3; ++i) {
		if (name == formNames[i]) {
			std::cout << "Intern creates " << formNames[i] << std::endl;
			for (int j = 0; j < 3; ++j) {
				if (j != i)
					delete forms[j];
			}
			return forms[i];
		}
	}
	for (int i = 0; i < 3; ++i)
		delete forms[i];
	throw Intern::UnknownFormException();
}

/**********************************exceptions**********************************/
const char*	Intern::UnknownFormException::what() const throw() {
	return "Intern-UnknownForm!";
}
