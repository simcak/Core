/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:49 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/13 16:59:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "Colors.hpp"

#include <iostream>
#include <string>
#include <exception>

#define GRADE_MAX 1
#define GRADE_MIN 150

class Form;

class Bureaucrat {
	private:
		const std::string	_name;
		unsigned int		_grade;

	public:
		/* ******* Orthodox Canonical Form ******* */
		// Default constructor
		Bureaucrat();
		// Constructor with parameters
		Bureaucrat(const std::string &, unsigned int);
		// Copy constructor
		Bureaucrat(const Bureaucrat &other);
		// Assignation operator
		Bureaucrat &operator=(const Bureaucrat &);
		// Destructor
		~Bureaucrat();

		/* ************** Functions ************** */
		const std::string	&getName() const;
		unsigned int		getGrade() const;
		void				incrementGrade();
		void				decrementGrade();
		void				signForm(Form &);

		/* ********** Exception Classes ********** */
		// too high
		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		// too low
		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os, Bureaucrat const &bure);

#endif
