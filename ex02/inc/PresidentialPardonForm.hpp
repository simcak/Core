/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:45:05 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/08 13:38:42 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

#include "Macros.hpp"
#include "AForm.hpp"

#include <string>
// #include <iostream>

class PresidentialPardonForm : public AForm
{
	private:
		const std::string	_target;

	public:
		/************************Orthodox Canonical Form***********************/
		PresidentialPardonForm();
		PresidentialPardonForm(std::string);
		PresidentialPardonForm(const PresidentialPardonForm &);
		PresidentialPardonForm &operator=(const PresidentialPardonForm &);
		~PresidentialPardonForm();

		/********************************getters*******************************/
		const std::string		&getTarget() const;

		/****************************member function***************************/
		void	execute(const Bureaucrat& executor) const; // overriden AForm

		/**********************************************************************/
};

#endif
