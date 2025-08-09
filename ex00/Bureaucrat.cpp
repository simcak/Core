/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:39:25 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/07 14:13:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Unnamed Bureaucrat"), _grade(GRADE_MIN) {}

Bureaucrat::Bureaucrat(std::string const &name, unsigned int grade)
: _name(name) {
	if (grade < GRADE_MAX)
		throw Bureaucrat::GradeTooHighException();
	if (grade > GRADE_MIN)
		throw Bureaucrat::GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src)
: _name(src._name), _grade(src._grade) {
	*this = src;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &src) {
	if (this != &src) {
		_grade = src._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << BR "Bureaucrat destructor called" RST << std::endl;
}

const std::string &Bureaucrat::getName(void) const {
	return _name;
}

unsigned int Bureaucrat::getGrade(void) const {
	return _grade;
}

void Bureaucrat::incrementGrade() {
	if (_grade - 1 < GRADE_MAX)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
}

void Bureaucrat::decrementGrade() {
	if (_grade + 1 > GRADE_MIN)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
}


const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade is too low!";
}

std::ostream &operator<<(std::ostream &os, Bureaucrat const &bure) {
	os << bure.getName() << ", bureaucrat grade " << bure.getGrade() << ".";
	return os;
}
