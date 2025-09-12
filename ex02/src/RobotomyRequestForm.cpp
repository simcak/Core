/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:45 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/12 16:24:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RobotomyRequestForm.hpp"

/***************************Orthodox Canonical Form****************************/
RobotomyRequestForm::RobotomyRequestForm()
	: AForm("Robotomy Request Form", 77, 55), _target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string target)
	: AForm("Robotomy Request Form", 77, 55), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &original)
	: AForm(original), _target(original._target) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &src) {
	(void)src;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << BR "RobotomyRequestForm destructor called" RST << std::endl;
}

/***********************************getters************************************/
const std::string&	RobotomyRequestForm::getTarget() const { return _target; }

/*******************************member functions*******************************/
void	RobotomyRequestForm::execute(const Bureaucrat& executor) const {
	if (getSignStatus() == false)
		throw AForm::NotSignedException();
	else if (executor.getGrade() > this->getExecuteGrade())
		throw AForm::GradeTooLowException();
	else {
		std::cout << executor.getName() << " executed " << this->getName() << std::endl;
	}
}
