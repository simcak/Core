/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:01:23 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/30 16:46:58 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

#include "Macros.hpp"

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

/**
 * AForm is Abstract - that is where the 1st char comes from. And thats because
 * of the PURE VIRTUAL FUNCTION execute().
 * AForm says: “Every form must have an execute(), but I don’t know how to do it
 * here.”
 */
class AForm
{
	private:
		const std::string	_name;
		bool				_is_signed;
		const int			_sign_grade;
		const int			_execute_grade;

	public:
		/************************Orthodox Canonical Form***********************/
		AForm();
		AForm(const std::string &, const int, const int);
		AForm(const AForm &);
		AForm &operator=(const AForm &);
		~AForm();
		/********************************getters*******************************/
		const std::string	&getName() const;
		bool				getSignStatus() const;
		unsigned int		getSignGrade() const;
		unsigned int		getExecuteGrade() const;
		/****************************member function***************************/
		void			checkGrade(const int) const;
		void			beSigned(Bureaucrat &);
		virtual void	execute(Bureaucrat const &) const = 0;	// ex02
		/******************************exceptions******************************/
		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		/**********************************************************************/
};

std::ostream &operator<<(std::ostream &, const AForm &);

#endif