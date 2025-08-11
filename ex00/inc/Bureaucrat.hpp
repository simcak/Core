/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:49 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/11 13:59:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

#define GRADE_MAX 1
#define GRADE_MIN 150

#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"
#define BRERR	"\033[1;31mError: \033[0m"

class Bureaucrat {
	private:
		const std::string	_name;
		unsigned int		_grade;

	public:
		/* ******* Orthodox Canonical Form ******* */
		// Default constructor
		Bureaucrat();
		// Constructor with parameters
		Bureaucrat(const std::string &name, unsigned int grade);
		// Copy constructor
		Bureaucrat(const Bureaucrat &other);
		// Assignation operator
		Bureaucrat &operator=(const Bureaucrat &other);
		// Destructor
		~Bureaucrat();

		/* ************** Functions ************** */
		const std::string	&getName(void) const;
		unsigned int		getGrade(void) const;
		void				incrementGrade();
		void				decrementGrade();

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
