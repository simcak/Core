/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:06 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/12 16:09:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		const std::string	_target;

	public:
		/************************Orthodox Canonical Form***********************/
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string);
		ShrubberyCreationForm(const ShrubberyCreationForm &);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &);
		~ShrubberyCreationForm();

		/********************************getters*******************************/
		const std::string	&getTarget() const;

		/****************************member function***************************/
		void	execute(const Bureaucrat& executor) const; // everriden AForm

		/**********************************************************************/
};

#endif
