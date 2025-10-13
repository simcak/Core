/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:37 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 12:53:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		const std::string	_target;

	public:
		/************************Orthodox Canonical Form***********************/
		RobotomyRequestForm();
		RobotomyRequestForm(const std::string);
		RobotomyRequestForm(const RobotomyRequestForm &);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &);
		~RobotomyRequestForm();

		/********************************getters*******************************/
		const std::string	&getTarget() const;

		/****************************member function***************************/
		void	makeNoise() const;
		void	execute(const Bureaucrat& executor) const; // overriden AForm

		/**********************************************************************/
};

#endif
