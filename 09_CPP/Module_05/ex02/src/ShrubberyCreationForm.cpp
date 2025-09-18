/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:44:19 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 13:35:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"
#include <fstream>

/***************************Orthodox Canonical Form****************************/
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("Shrubbery Creation Form", 145, 137), _target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target)
	: AForm("Shrubbery Creation Form", 145, 137), _target(target) {}

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
		std::cout << "🚀\t" << executor.getName() << " executed " << this->getName() << std::endl;

		std::ifstream ifs(("./art/" + _target + "Tree.txt").c_str());
		if (ifs) {
			std::ofstream ofs;
			ofs.open((_target + "_shrubbery").c_str());
			ofs << ifs.rdbuf();
			ifs.close();
			ofs.close();
		}
		else
			std::cout << BRERR << _target << "Tree.txt was not found" << std::endl;
	}
}
