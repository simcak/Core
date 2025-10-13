/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:45:02 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 13:35:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PresidentialPardonForm.hpp"

/***************************Orthodox Canonical Form****************************/
PresidentialPardonForm::PresidentialPardonForm()
	: AForm("Presidential Pardon Form", 25, 5), _target("default") {}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: AForm("Presidential Pardon Form", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &ppf)
	: AForm(ppf), _target(ppf._target) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &src) {
	(void)src;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << BR "PresidentialPardonForm destructor called" RST << std::endl;
}

/***********************************getters************************************/
const std::string&	PresidentialPardonForm::getTarget() const { return _target; }

/*******************************member functions*******************************/
void	PresidentialPardonForm::execute(const Bureaucrat& executor) const {
	if (this->getSignStatus() == false)
		throw AForm::NotSignedException();
	else if (executor.getGrade() > this->getExecuteGrade())
		throw AForm::GradeTooLowException();
	else {
		std::cout << "🚀\t" << executor.getName() << " executed " << this->getName() << std::endl;
		std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
	}
}
