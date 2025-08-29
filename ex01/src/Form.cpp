/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:01:44 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/29 16:58:53 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Form.hpp"
#include "../inc/Bureaucrat.hpp"

/***************************Orthodox Canonical Form****************************/
Form::Form() : _name("FormX"), _is_signed(false), _sign_grade(42), _execute_grade(24) {}

Form::Form(const std::string &name, const int sg, const int eg) :
	_name(name), _is_signed(false), _sign_grade(sg), _execute_grade(eg) {
	checkGrade(sg);
	checkGrade(eg);
}

Form::Form(const Form &other) :
	_name(other.getName()), _is_signed(other.getSignStatus()),
	_sign_grade(other.getSignGrade()), _execute_grade(other.getExecuteGrade()) {}

Form&	Form::operator=(const Form &other) {
	if (this != &other)
		_is_signed = other.getSignStatus();
	return *this;
}

Form::~Form() {
	std::cout << BR << "Form Destructor called" << RST << std::endl;
}

/***********************************getters************************************/
const std::string&	Form::getName() const { return _name; }
bool				Form::getSignStatus() const { return _is_signed; }
unsigned int		Form::getSignGrade() const { return _sign_grade; }
unsigned int		Form::getExecuteGrade() const { return _execute_grade; }

/*******************************member functions*******************************/
void	Form::checkGrade(const int grade) const {
	if (grade > GRADE_MIN)
		throw Form::GradeTooLowException();
	else if (grade < GRADE_MAX)
		throw Form::GradeTooHighException();
}

void	Form::beSigned(Bureaucrat &bure) {
	if (bure.getGrade() > getSignGrade()) {
		throw Form::GradeTooLowException();
	}
	std::cout << bure.getName() << " signed " << getName() << std::endl;
	_is_signed = true;
}

/**********************************exceptions**********************************/
const char*	Form::GradeTooLowException::what() const throw() {
	return "Form-GradeTooLow";
}

const char*	Form::GradeTooHighException::what() const throw() {
	return "Form-GradeTooHigh";
}

/***********************************overload***********************************/
std::ostream&	operator<<(std::ostream &osm, const Form &form) {
	std::string status = form.getSignStatus() ? (BG "true" RST) : (BR "false" RST);

	osm << "Form Name:\t" << form.getName()
		<< "\nIs signed:\t" << status
		<< "\nSign Grade:\t" << form.getSignGrade()
		<< "\nExecute Grade: \t" << form.getExecuteGrade();
	return osm;
}
