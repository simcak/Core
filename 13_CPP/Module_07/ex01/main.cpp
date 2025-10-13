/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:18 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/13 15:47:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

void	printInt(const int &x) { std::cout << "[" << x << "] "; }

void	printStr(const std::string &x) { std::cout << "[" << x << "] "; }

void	quadro(int &num) { num *= 4; }

static bool	isSmallAlpha(std::string &str, int i) {
	return (str[i] >= 'a' && str[i] <= 'z');
}

void	capitalize(std::string &str) {
	for (size_t i = 0; i < str.length(); i++)
		if (isSmallAlpha(str, i))
			str[i] ^= 32;
}


int	main(void) {
	int			ints[] = {-7, -5, -4, -2, 0, 1, 2, 5, 7, 8, 9, 10};
	std::string	strs[] = {"HellO", "World!\0 and you", "4~ever", "young."};

	/************************************INT***********************************/
	std::cout << BY "Print integers:" RST << std::endl;
	::iter(ints, 12, printInt);
	std::cout << std::endl;
	
	std::cout << "\n" BB "Quadro integers:" RST << std::endl;
	::iter(ints, 12, quadro);
	::iter(ints, 12, printInt);
	std::cout << std::endl;
	
	/**********************************STRINGS*********************************/
	std::cout << "\n" BY "Print strings:" RST << std::endl;
	::iter(strs, 4, printStr);
	std::cout << std::endl;
	
	std::cout << "\n" BB "CAPITALIZE STRINGS:" RST << std::endl;
	::iter(strs, 3, capitalize);
	::iter(strs, 4, printStr);
	std::cout << std::endl;

	return 0;
}
