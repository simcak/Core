/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:06 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/14 16:59:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

#include "Macros.hpp"
#include <iostream>
#include <string>

class ShrubberyCreationForm
{
	private:
		std::string	_target;
		const int	_sign_grade;
		const int	_execute_grade;

	public:
		/************************Orthodox Canonical Form***********************/
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string, const int, const int);
		ShrubberyCreationForm(const ShrubberyCreationForm &);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &);
		~ShrubberyCreationForm();
		/********************************getters*******************************/
		const int	getSignGrade() const;
		const int	getExecuteGrade() const;
		/****************************member function***************************/
		void		checkGrade(const int) const;
		/******************************exceptions******************************/
		/**********************************************************************/
};

std::ostream &operator<<(std::ostream &, const ShrubberyCreationForm &);

#endif
