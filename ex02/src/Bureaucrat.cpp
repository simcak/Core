/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:39:25 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/12 15:00:15 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bureaucrat.hpp"
#include "../inc/AForm.hpp"

/***************************Orthodox Canonical Form****************************/
Bureaucrat::Bureaucrat() : _name("X"), _grade(GRADE_MIN) {}

Bureaucrat::Bureaucrat(const std::string &name, unsigned int grade) : _name(name) {
	if (grade < GRADE_MAX)
		throw Bureaucrat::GradeTooHighException();
	if (grade > GRADE_MIN)
		throw Bureaucrat::GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: _name(other._name), _grade(other._grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	if (this != &other)
		_grade = other.getGrade();
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << BR "Bureaucrat destructor called" RST << std::endl;
}

/***********************************getters************************************/
const std::string&	Bureaucrat::getName() const { return _name; }
unsigned int		Bureaucrat::getGrade() const { return _grade; }

/*******************************member functions*******************************/
void	Bureaucrat::incrementGrade() {
	try {
		if (getGrade() - 1 < GRADE_MAX)
			throw Bureaucrat::GradeTooHighException();
		_grade--;
	}
	catch(const std::exception& e) {
		std::cout << BREXC << getName() << "cannot ⬆️ increment because: " <<
		e.what() << std::endl;
	}
}

void	Bureaucrat::decrementGrade() {
	try {
		if (getGrade() + 1 > GRADE_MIN)
			throw Bureaucrat::GradeTooLowException();
		_grade++;
	}
	catch(const std::exception& e) {
		std::cout << BREXC << getName() << "cannot ⬇️ decrement because: " <<
		e.what() << std::endl;
	}
}

void	Bureaucrat::signForm(AForm &form) {
	try {
		form.beSigned(*this);
	}
	catch(const std::exception& e) {
		std::cout << BREXC << getName() << " couldn't ✍️ sign " <<
		form.getName() << " because " << e.what() << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm &form) const {
	try {
		form.execute(*this);
	}
	catch(const std::exception& e) {
		std::cout << BREXC << getName() << " couldn't 🚀 execute " <<
		form.getName() << " because " << e.what() << std::endl;
	}
}

/**********************************exceptions**********************************/
const char*	Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bure-GradeTooHigh!";
}

const char*	Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bure-GradeTooLow!";
}

/***********************************overload***********************************/
std::ostream&	operator<<(std::ostream &osm, const Bureaucrat &bure) {
	osm << bure.getName() << ", bureaucrat grade " << bure.getGrade() << ".";
	return osm;
}
