/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:39:29 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/09 18:19:11 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bureaucrat.hpp"

/**
 * @brief Main function == testing function.
 */
int main() {
	// Start testing with wrong grates, than wrong movement of grates, than ok
	std::cout <<
		BY "===============Initiate with a wrong grades==============" RST <<
	std::endl;

	int grade = 151;
	std::cout << "grade = " << grade << std::endl;
	try {
		Bureaucrat Josef("Pepik", grade);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "------------------------" << std::endl;

	grade = 0;
	std::cout << "grade = " << grade << std::endl;
	try {
		Bureaucrat Joza("Pepicek", grade);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// Initiate with a correct grade and perform wrong increment or decrement
	std::cout <<
		BY "===========Perform with wrong (in/de)crement=============" RST <<
	std::endl;

	grade = 1;
	try {
		Bureaucrat NonameX("Steve", grade);
		std::cout << NonameX << std::endl;
		NonameX.decrementGrade();
		NonameX.incrementGrade();
		NonameX.incrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "------------------------" << std::endl;

	grade = 150;
	try {
		Bureaucrat NonameY("Eragon", grade);
		std::cout << NonameY << std::endl;
		NonameY.decrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// Testing of well working apparat. It will end with destructors.
	std::cout <<
		BY "==================Should work just fine==================" RST <<
	std::endl;

	grade = 1;
	try {
		Bureaucrat NamedX("Marvin", grade);
		std::cout << NamedX << std::endl;
		NamedX.decrementGrade();
		std::cout << NamedX << std::endl;
		NamedX.decrementGrade();
		std::cout << NamedX << std::endl;
		NamedX.incrementGrade();
		std::cout << NamedX << std::endl;

		std::cout << BG << "LOOOOOOP" << RST << std::endl;
		for (int i = 0; i <= 11; ++i) {
			NamedX.decrementGrade();
			std::cout << NamedX << std::endl;
		}
		std::cout << BR << "END LOOP" << RST << std::endl;

		Bureaucrat NamedY(NamedX);
		std::cout << "I am NamedY a copy of NamedX: " << NamedY << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
