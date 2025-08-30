/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:01:44 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/30 16:21:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"

/***************************Orthodox Canonical Form****************************/
AForm::AForm() : _name("aFormX"), _is_signed(false), _sign_grade(42), _execute_grade(24) {}

AForm::AForm(const std::string &name, const int sg, const int eg)
	: _name(name), _is_signed(false), _sign_grade(sg), _execute_grade(eg) {
		checkGrade(sg);
		checkGrade(eg);
}

AForm::AForm(const AForm &other)
	: _name(other.getName()), _is_signed(other.getSignStatus()),
	_sign_grade(other.getSignGrade()), _execute_grade(other.getExecuteGrade()) {}

AForm&	AForm::operator=(const AForm &other) {
	if (this != &other)
		_is_signed = other.getSignStatus();
	return *this;
}

AForm::~AForm() {
	std::cout << BR << "AForm Destructor called" << RST << std::endl;
}

/***********************************getters************************************/
const std::string&	AForm::getName() const { return _name; }
bool				AForm::getSignStatus() const { return _is_signed; }
unsigned int		AForm::getSignGrade() const { return _sign_grade; }
unsigned int		AForm::getExecuteGrade() const { return _execute_grade; }

/*******************************member functions*******************************/
void	AForm::checkGrade(const int grade) const {
	if (grade > GRADE_MIN)
		throw AForm::GradeTooLowException();
	else if (grade < GRADE_MAX)
		throw AForm::GradeTooHighException();
}

void	AForm::beSigned(Bureaucrat &bure) {
	if (bure.getGrade() > getSignGrade()) {
		throw AForm::GradeTooLowException();
	}
	std::cout << bure.getName() << " signed " << getName() << std::endl;
	_is_signed = true;
}

/**********************************exceptions**********************************/
const char*	AForm::GradeTooLowException::what() const throw() {
	return "AForm-GradeTooLow";
}

const char*	AForm::GradeTooHighException::what() const throw() {
	return "AForm-GradeTooHigh";
}

/***********************************overload***********************************/
std::ostream&	operator<<(std::ostream &osm, const AForm &aForm) {
	std::string status = aForm.getSignStatus() ? (BG "true" B) : (BR "false" B);

	osm << B "AForm Name:\t" << aForm.getName()
		<< "\nIs signed:\t" << status
		<< "\nSign Grade:\t" << aForm.getSignGrade()
		<< "\nExecute Grade: \t" << aForm.getExecuteGrade()
		<< RST;
	return osm;
}
