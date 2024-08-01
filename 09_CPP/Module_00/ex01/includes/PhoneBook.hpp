/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:57:12 by psimcak           #+#    #+#             */
/*   Updated: 2024/08/01 07:01:49 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Agenda.hpp"
#include "Contact.hpp"

class PhoneBook
{
	public:
		Contact	contacts[8];
		int		contact_id;

		PhoneBook( void );
		void initContact(std::string data[4]);
		void addContact(std::string data[4]);
		void searchContact();
		~PhoneBook();
};
