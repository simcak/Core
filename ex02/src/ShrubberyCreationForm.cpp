/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:19 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/12 16:16:56 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"

/***************************Orthodox Canonical Form****************************/
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("Shrubbery Creation Form", 145, 135), _target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target)
	: AForm("Shrubbery Creation Form", 145, 135), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &original)
	: AForm(original), _target(original._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src) {
	(void)src;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << BR "ShrubberyCreationForm destructor called" RST << std::endl;
}

/***********************************getters************************************/
const std::string&	ShrubberyCreationForm::getTarget() const { return _target; }

/*******************************member functions*******************************/
void	ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	if (getSignStatus() == false)
		throw AForm::NotSignedException();
	else if (executor.getGrade() > getExecuteGrade())
		throw AForm::GradeTooLowException();
	else {
		std::cout << executor.getName() << " executed " << this->getName() << std::endl;
	}
}
