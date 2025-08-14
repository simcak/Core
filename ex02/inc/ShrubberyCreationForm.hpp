/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:06 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/14 16:01:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

#include "Colors.hpp"
#include <iostream>
#include <string>

class ShrubberyCreationForm
{
	private:
		std::string	&target;
		const int	_sign_grade;
		const int	_execute_grade;

	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const int, const int);
		ShrubberyCreationForm(const ShrubberyCreationForm &);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &);
		~ShrubberyCreationForm();
};

std::ostream &operator<<(std::ostream &, const ShrubberyCreationForm &);

#endif
