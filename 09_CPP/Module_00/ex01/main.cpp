/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:51:38 by psimcak           #+#    #+#             */
/*   Updated: 2024/08/01 07:09:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/PhoneBook.hpp"

int	main(void)
{
	PhoneBook	phonebook;
	std::string	action;
	std::string	data[4];

	phonebook.contact_id = 0;
	while (42) {
		std::cout << BBB << "PhoneBook> " << RST;
		std::getline(std::cin, action);
		if (action == "ADD")
		{
			phonebook.initContact(data);
			phonebook.addContact(data);
		}
		else if (action == "SEARCH")
		{
			phonebook.searchContact();
		}
		else if (action == "EXIT")
			break ;
		else
			std::cout << RED << "Invalid command, " << RST << "try: ADD/SEARCH/EXIT" << std::endl;
	}
	return (SUCCESS);
}