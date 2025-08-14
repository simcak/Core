/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:19 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/14 17:13:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"

/***************************Orthodox Canonical Form****************************/
ShrubberyCreationForm::ShrubberyCreationForm()
	: _target("target"), _sign_grade(42), _execute_grade(24) {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string t, const int sg, const int eg)
	: _target(t), _sign_grade(sg), _execute_grade(eg) {
	checkGrade(sg);
	checkGrade(eg);
}

/***********************************getters************************************/
const int	ShrubberyCreationForm::getSignGrade() const {
	return _sign_grade;
}
	
const int	ShrubberyCreationForm::getExecuteGrade() const {
	return _execute_grade;
}

/*******************************member functions*******************************/
void	ShrubberyCreationForm::checkGrade(const int grade) const {
	if (grade < GRADE_MAX) {
		throw ;
	}
	else if (grade > GRADE_MIN) {
		throw ;
	}
}

/**********************************exceptions**********************************/


/***********************************overload***********************************/

