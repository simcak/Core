/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:49 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 14:59:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "Macros.hpp"

#include <iostream>
#include <string>
#include <exception>

class AForm;

class Bureaucrat {
	private:
		const std::string	_name;
		unsigned int		_grade;

	public:
		/***********************Orthodox Canonical Form************************/
		Bureaucrat();
		Bureaucrat(const std::string &, unsigned int);
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &);
		~Bureaucrat();

		/********************************getters*******************************/
		const std::string	&getName() const;
		unsigned int		getGrade() const;

		/****************************member function***************************/
		void				incrementGrade();
		void				decrementGrade();
		void				signForm(AForm &);
		void				executeForm(AForm &) const;

		/******************************exceptions******************************/
		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os, Bureaucrat const &bure);

#endif
