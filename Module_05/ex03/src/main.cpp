/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:43:24 by psimcak           #+#    #+#             */
/*   Updated: 2025/09/17 15:02:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Macros.hpp"
#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/Intern.hpp"

int main(int ac, char **av) {
	std::cout <<
		BY "===========Buro-Playground where we test & play===========" RST <<
	std::endl;

	Bureaucrat frank("Frank", 42);
	Bureaucrat mario("Mario", 7);
	Bureaucrat humphrey("Sir Humphrey Appleby", 1);
	std::cout << frank << "\n" << mario << "\n" << humphrey << std::endl;

	std::cout << BY "\nInterns-----------------" RST << std::endl;
	if (ac == 3) {
		try {
			Intern	intern;
			AForm*	form;

			form = intern.makeForm(av[1], av[2]);
			std::cout << *form << std::endl;
			frank.signForm(*form);
			humphrey.executeForm(*form);
			delete form;
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	else {
		std::cout << BR "Wrong number of arguments " RST;
		std::cout << "use: ('shrubbery' || 'robotomy' || 'pardon') && <target>" << std::endl;
		return 1;
	}
	return 0;
}
