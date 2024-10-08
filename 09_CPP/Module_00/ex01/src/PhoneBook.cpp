/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:03:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/02 18:43:51 by psimcak          ###   ########.fr       */
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
	std::cout << BWT << "Enter Contact Information" << RST << std::endl;
	safeGetline(data[0], "First Name:\t", 0);
	safeGetline(data[1], "Last Name:\t", 0);
	safeGetline(data[2], "Nickname:\t", 0);
	safeGetline(data[3], "Phone Number:\t", 0);
	safeGetline(data[4], "Darkest Secret:\t", 0);
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

/**
 * safeTable - print table line by line
 */
void	safeTable(PhoneBook *phonebook, int i)
{
	std::cout << std::setw(10) << i + 1 << "|";
	if (phonebook->contacts[i].first_name.length() > 10)
		std::cout << std::setw(9) << phonebook->contacts[i].first_name.substr(0, 9) << ".|";
	else
		std::cout << std::setw(10) << phonebook->contacts[i].first_name << "|";
	if (phonebook->contacts[i].last_name.length() > 10)
		std::cout << std::setw(9) << phonebook->contacts[i].last_name.substr(0, 9) << ".|";
	else
		std::cout << std::setw(10) << phonebook->contacts[i].last_name << "|";
	if (phonebook->contacts[i].nickname.length() > 10)
		std::cout << std::setw(9) << phonebook->contacts[i].nickname.substr(0, 9) << "." << std::endl;
	else
		std::cout << std::setw(10) << phonebook->contacts[i].nickname << std::endl;	
}

/**
 * search contact in phonebook
 */
void	PhoneBook::searchContact( void )
{
	int			i = -1;
	std::string	input_index;

	if (this->contact_id == 0)
	{
		std::cout << RED << "No contacts found" << RST << std::endl;
		return ;
	}
	std::cout << BBB << "*******************************************" << RST << std::endl;
	std::cout << "     Index|First Name| Last Name|  Nickname" << std::endl;
	while (++i < this->contact_id) {
		safeTable(this, i);
	}
	std::cout << BBB << "*******************************************" << RST << std::endl;
	safeGetline(input_index, "Enter the index of the entry to display: ", this->contact_id);
	i = input_index[0] - '0' - 1;
	std::cout << "First Name:\t" << this->contacts[i].first_name << std::endl;
	std::cout << "Last Name:\t" << this->contacts[i].last_name << std::endl;
	std::cout << "Nickname:\t" << this->contacts[i].nickname << std::endl;
	std::cout << "Phone Number:\t" << this->contacts[i].phone_number << std::endl;
	std::cout << "Darkest Secret:\t" << this->contacts[i].darkest_secret << std::endl;
	std::cout << BBB << "*******************************************" << RST << std::endl;
}

/**
 * PhoneBook destructor
 */
PhoneBook::~PhoneBook()
{
	std::cout << RED << "PhoneBook destroyed" << RST << std::endl;
}