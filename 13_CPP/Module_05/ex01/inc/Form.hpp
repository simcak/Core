/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:01:23 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/13 16:59:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include "Colors.hpp"

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool				_is_signed;
		const int			_sign_grade;
		const int			_execute_grade;

	public:
		Form();
		Form(const std::string &, const int, const int);
		Form(const Form &);
		Form &operator=(const Form &);
		~Form();

		const std::string	&getName() const;
		bool				getSignStatus() const;
		unsigned int		getSignGrade() const;
		unsigned int		getExecuteGrade() const;

		void	checkGrade(const int) const;
		void	beSigned(Bureaucrat &);

		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &, const Form &);

#endif