/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:37 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/29 14:59:19 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

#include "Macros.hpp"

class RobotomyRequestForm
{
	private:
		const int	_sign_grade;
		const int	_execute_grade;

	public:
		/************************Orthodox Canonical Form***********************/
		RobotomyRequestForm();
		RobotomyRequestForm(const int, const int);
		RobotomyRequestForm(const RobotomyRequestForm &);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &);
		~RobotomyRequestForm();
		/********************************getters*******************************/
		const int	getSignGrade() const;
		const int	getExecuteGrade() const;
		/****************************member function***************************/
		void	checkGrade(const int) const;
		/******************************exceptions******************************/
		/**********************************************************************/
};

#endif
