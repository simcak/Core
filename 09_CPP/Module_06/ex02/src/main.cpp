/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:37:19 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/08 13:12:39 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Identifier.hpp"
#include "../inc/Macros.hpp"

int main(int ac, char **av) {

	if (ac == 2) {
		int len = std::atoi(av[1]);
		std::srand(static_cast<unsigned>(time(NULL)));
		
		std::cout << BY "GENERATING RANDOM CLASSES:" RST << std::endl;
		Base* bases[len];
		for (int i = 0; i < len; ++i) {
			bases[i] = generate();
		}

		for (int i = 0; i < len; ++i) {
			std::cout << "\n" BY << (i + 1) << "th IDENTIFICATION:" << RST << std::endl;
			identifyFromPtr(bases[i]);
			identifyFromRef(*bases[i]);
		}
		
		for (int i = 0; i < len; ++i) {
			delete bases[i];
		}
	}
	else
		std::cout << BRERR "use 2nd arg telling how many classes to generate" RST << std::endl;

	return 0;
}
