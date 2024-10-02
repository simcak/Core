/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safeGetline.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 06:11:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 18:46:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Agenda.hpp"

/**
 * numIsValid - check if phone number is valid
 */
static bool	numIsNotValid(std::string &str)
{
	int i = -1;
	
	if (str[0] == '+')
	{
		if (!str[1])
		{
			std::cout << RED << "Invalid phone number, try again: " << RST << std::endl;
			return (true);
		}
		i++;
	}
	while (str[++i]) {
		if (!isdigit(str[i]))
		{
			std::cout << RED << "Invalid phone number, try again: " << RST << std::endl;
			return (true);
		}
	}
	return (false);
}

/**
 * safeGetline - get line from user and check if it's empty
 */
void	safeGetline(std::string &dest, std::string mes, int index)
{
	std::cout << mes;
	std::getline(std::cin, dest);
	while (dest.empty()) {
		std::cout << RED << "Cannot be empty." << RST << std::endl;
		std::cout << mes;
		std::getline(std::cin, dest);
		if (mes == "Phone Number:\t")
			if (numIsNotValid(dest))
				safeGetline(dest, mes, 0);
	}
	if (mes == "Phone Number:\t")
		if (numIsNotValid(dest))
			safeGetline(dest, mes, 0);
	if (mes == "Enter the index of the entry to display: ")
	{
		if (!isdigit(dest[0]) || dest[1] || !(dest[0] >= '1' && dest[0] <= '8') || dest[0] - '0' > index)
		{
			std::cout << RED << "Invalid index, try again: " << RST << std::endl;
			safeGetline(dest, mes, index);
		}
	}
}
