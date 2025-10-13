/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:45 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 14:48:27 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/***************************Orthodox Canonical Form****************************/
RobotomyRequestForm::RobotomyRequestForm()
	: AForm("Robotomy Request Form", 72, 45), _target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string target)
	: AForm("Robotomy Request Form", 72, 45), _target(target) {}

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
void	RobotomyRequestForm::makeNoise() const {
	std::cout << BB;
	for (int i = 0; i < 10; ++i) {
		std::cout << "\aBrrrrr..." << std::flush;
		usleep(100000); // 100ms
	}
	std::cout << "\aVrrrrrr... \aBZZZZZZT!!!" RST << std::endl;
}

void	RobotomyRequestForm::execute(const Bureaucrat& executor) const {
	if (this->getSignStatus() == false)
		throw AForm::NotSignedException();
	else if (executor.getGrade() > this->getExecuteGrade())
		throw AForm::GradeTooLowException();
	else {
		std::cout << "🚀\t" << executor.getName() << " executed " << this->getName() << std::endl;

		std::srand(static_cast<unsigned int>(std::time(0)));
		int	random_number = std::rand();
		if (random_number % 2 == 0) {
			this->makeNoise();
			std::cout << _target << BG " robotomized" RST << std::endl;
		}
		else 
			std::cout << _target << BR " robotomy failed" RST << std::endl;
	}
}
