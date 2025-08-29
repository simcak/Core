/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:39:29 by psimcak           #+#    #+#             */
/*   Updated: 2025/08/29 17:19:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bureaucrat.hpp"
#include "../inc/Form.hpp"
#include "../inc/Colors.hpp"

/**
 * @brief Main function == testing function.
 */
int main() {
	// Testing the Orthodox Canonical Form
	std::cout <<
		BY "==============Orthodox Canonical Form Tests==============" RST <<
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
	
	try {
		Form f0; // Default constructor
		Form f1("Form1", 50, 30);
		Form f2("Form2", 100, 80);
		Form f3(f1); // Copy constructor
		Form f4("TopSecret", 2, 1);
		f4 = f2; // Copy assignment operator

		std::cout << "Form 0: " << f0.getName() << ", Sign Grade: " << f0.getSignGrade()
				  << ", Execute Grade: " << f0.getExecuteGrade() << " is signed: " << f0.getSignStatus() << std::endl;
		std::cout << "Form 1: " << f1.getName() << ", Sign Grade: " << f1.getSignGrade()
				  << ", Execute Grade: " << f1.getExecuteGrade() << " is signed: " << f1.getSignStatus() << std::endl;
		std::cout << "Form 2: " << f2.getName() << ", Sign Grade: " << f2.getSignGrade()
				  << ", Execute Grade: " << f2.getExecuteGrade() << " is signed: " << f2.getSignStatus() << std::endl;
		std::cout << "Form 3: " << f3.getName() << ", Sign Grade: " << f3.getSignGrade()
				  << ", Execute Grade: " << f3.getExecuteGrade() << " is signed: " << f3.getSignStatus() << std::endl;
		std::cout << "Form 4: " << f4.getName() << ", Sign Grade: " << f4.getSignGrade()
				  << ", Execute Grade: " << f4.getExecuteGrade() << " is signed: " << f4.getSignStatus() << std::endl;
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}

	std::cout <<
		BY "===============Initiate with a wrong grades==============" RST <<
	std::endl;

	try {
		Bureaucrat b0("Marvin0", 0);
		Bureaucrat b1("Marvin1", 151);
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}
	try {
		Form f0("Form0", 0, 30);
		Form f1("Form1", 30, 0);
		Form f2("Form2", 151, 30);
		Form f3("Form3", 30, 151);
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}

	std::cout <<
		BY "==================Should work just fine==================" RST <<
	std::endl;

	try {
		Bureaucrat b0("Marvin0", 50);
		Bureaucrat b1("Marvin1", 51);

		Form f0("Form0", 50, 30);
		Form f1("Form1", 50, 30);

		b0.signForm(f0); // Should succeed
		std::cout << BB << b0 << B"\n" << f0 << RST << std::endl;
		b1.signForm(f1); // Should throw GradeTooLowException
		std::cout << BB << b1 << B"\n" << f1 << RST << std::endl;
		
		b0.decrementGrade();
		b1.incrementGrade();
		
		b0.signForm(f0);
		std::cout << BB << b0 << B"\n" << f0 << RST << std::endl;
		b1.signForm(f1); // Should succeed now
		std::cout << BB << b1 << B"\n" << f1 << RST << std::endl;

		Form f2("Form2", 100, 80);
		std::cout << "New Form\n" << B << f2 << RST << std::endl;
		f2 = f1;
		std::cout << "f2 = f1\n" << B << f2 << RST << std::endl;
	} catch (const std::exception &e) {
		std::cout << BREXC << e.what() << std::endl;
	}
}
