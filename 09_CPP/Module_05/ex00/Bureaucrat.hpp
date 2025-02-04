/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:49 by psimcak           #+#    #+#             */
/*   Updated: 2025/02/04 20:39:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat {
	private:
		const std::string	_name;
		int					_grade;

	public:
		/* ******* Orthodox Canonical Form ******* */
		Bureaucrat(const std::string &name, int grade);	// Constructor
		Bureaucrat(const Bureaucrat &src);	// Copy constructor
		Bureaucrat &operator=(const Bureaucrat &src);	// Assignation operator
		~Bureaucrat();	// Destructor

		/* ************** Functions ************** */
		const std::string	&getName(void) const;
		int					getGrade(void) const;
		void				incrementGrade(int num);
		void				decrementGrade(int num);

		/* ************** Exceptions ************* */
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
