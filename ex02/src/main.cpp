/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:43:24 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/15 16:25:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Macros.hpp"
#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"

int main() {
	// Testing the Orthodox Canonical Form
	std::cout <<
		BY "==============Orthodox Canonical Form Tests===============" RST <<
	std::endl;

	try {
		Bureaucrat b0; // Default constructor
		Bureaucrat b1("Bureaucrat1", 50);
		Bureaucrat b2("Bureaucrat2", 100);
		Bureaucrat b3(b1); // Copy constructor
		Bureaucrat b4("Mark", 42);
		b4 = b2; // Copy assignment operator

		std::cout << "Bureaucrat 0: " << b0.getName() << ", Grade: " << b0.getGrade() << std::endl;
		std::cout << "Bureaucrat 1: " << b1.getName() << ", Grade: " << b1.getGrade() << std::endl;
		std::cout << "Bureaucrat 2: " << b2.getName() << ", Grade: " << b2.getGrade() << std::endl;
		std::cout << "Bureaucrat 3: " << b3.getName() << ", Grade: " << b3.getGrade() << std::endl;
		std::cout << "Bureaucrat 4: " << b4.getName() << ", Grade: " << b4.getGrade() << std::endl;

		try {
			Bureaucrat b5("Bureaucrat5", 0); // Should throw GradeTooHighException
			std::cout << "Bureaucrat 5: " << b5.getName() << ", Grade: " << b5.getGrade() << std::endl;
		} catch (const std::exception &e) {
			std::cout << BREXC << e.what() << std::endl;
		}
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}

	std::cout <<
		BY "===============Initiate with a wrong grades===============" RST <<
	std::endl;

	try {
		Bureaucrat b0("Marvin0", 0);
		Bureaucrat b1("Marvin1", 151);
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}

	std::cout <<
		BY "===========Buro-Playground where we test & play===========" RST <<
	std::endl;

	Bureaucrat frank("Frank", 42);
	Bureaucrat mario("Mario", 7);
	Bureaucrat humphrey("Sir Humphrey Appleby", 1);
	std::cout << frank << "\n" << mario << "\n" << humphrey << std::endl;

	std::cout << BY "\nShrubberyCreationForm-----------------" RST << std::endl;
	ShrubberyCreationForm treeForm("fallen");
	std::cout << treeForm << std::endl;
	
	frank.signForm(treeForm);
	frank.executeForm(treeForm);
	
	std::cout << BY "\nRobotomyRequestForm-------------------" RST << std::endl;
	RobotomyRequestForm robotomyForm("Martin");
	std::cout << robotomyForm << std::endl;
	
	frank.signForm(robotomyForm);
	frank.executeForm(robotomyForm);
	
	std::cout << BY "\nPresidentialPardonForm----------------" RST << std::endl;
	PresidentialPardonForm pardonForm("Jack");
	std::cout << pardonForm << std::endl;

	frank.signForm(pardonForm);
	frank.executeForm(pardonForm);

	humphrey.executeForm(pardonForm);
	mario.signForm(pardonForm);
	mario.executeForm(pardonForm);

	std::cout << pardonForm << std::endl;

	humphrey.executeForm(pardonForm);

	return 0;
}
