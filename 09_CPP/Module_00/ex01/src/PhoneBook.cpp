/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:03:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/08/01 08:21:21 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PhoneBook.hpp"

/**
 * PhoneBook constructor
 */
PhoneBook::PhoneBook( void )
{
	std::cout << GRN << "PhoneBook created" << RST << std::endl;
}

/**
 * initialize values - runs for each contact separately
 */
void PhoneBook::initContact(std::string data[5])
{
	std::cout << BBB << "Enter Contact Information" << RST << std::endl;
	safeGetline(data[0], "First Name: ", 0);
	safeGetline(data[1], "Last Name: ", 0);
	safeGetline(data[2], "Nickname: ", 0);
	safeGetline(data[3], "Phone Number: ", 0);
	safeGetline(data[4], "Darkest Secret: ", 0);
}

/**
 * add contact to phonebook
 */
void PhoneBook::addContact(std::string data[5])
{
	int id = this->contact_id;
	if (id == 8)
		id--;

	this->contacts[id].first_name = data[0];
	this->contacts[id].last_name = data[1];
	this->contacts[id].nickname = data[2];
	this->contacts[id].phone_number = data[3];
	this->contacts[id].darkest_secret = data[4];
	
	std::cout << GRN << "✅ Contact [" << id + 1 << "] added" << RST << std::endl;

	this->contact_id++;
	if (this->contact_id > 7)
		this->contact_id = 8;
}

void	PhoneBook::searchContact( void )
{
	int			i = -1;
	std::string	input_index;

	if (this->contact_id == 0)
	{
		std::cout << RED << "No contacts found" << RST << std::endl;
		return ;
	}
	std::cout << "     Index|First Name| Last Name|  Nickname" << std::endl;
	while (++i < this->contact_id)
	{
		std::cout << std::setw(10) << i + 1 << "|";
		std::cout << std::setw(10) << this->contacts[i].first_name << "|";
		std::cout << std::setw(10) << this->contacts[i].last_name << "|";
		std::cout << std::setw(10) << this->contacts[i].nickname << std::endl;
	}
	safeGetline(input_index, "Enter index of the contact you want to see: ", this->contact_id);
	i = input_index[0] - '0' - 1;
	std::cout << "First Name: " << this->contacts[i].first_name << std::endl;
	std::cout << "Last Name: " << this->contacts[i].last_name << std::endl;
	std::cout << "Nickname: " << this->contacts[i].nickname << std::endl;
	std::cout << "Phone Number: " << this->contacts[i].phone_number << std::endl;
	std::cout << "Darkest Secret: " << this->contacts[i].darkest_secret << std::endl;
}

/**
 * PhoneBook destructor
 */
PhoneBook::~PhoneBook()
{
	std::cout << RED << "PhoneBook destroyed" << RST << std::endl;
}