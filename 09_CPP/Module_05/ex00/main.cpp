/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:39:29 by psimcak           #+#    #+#             */
/*   Updated: 2025/01/20 16:20:31 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	Bureaucrat *bureaucrat = new Bureaucrat("John", 1);
	std::cout << *bureaucrat << std::endl;

	delete bureaucrat;
	return 0;
}
