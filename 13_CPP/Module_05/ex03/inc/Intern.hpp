/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:54:48 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 16:30:27 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include "../inc/Macros.hpp"
#include "../inc/AForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"

#include <iostream>
#include <string>
#include <exception>

class Intern
{
	public:
		/***********************Orthodox Canonical Form************************/
		Intern();
		Intern(const Intern &);
		Intern &operator=(const Intern &);
		~Intern();

		/****************************member function***************************/
		AForm	*makeForm(std::string name, std::string target);

		/******************************exceptions******************************/
		class UnknownFormException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif