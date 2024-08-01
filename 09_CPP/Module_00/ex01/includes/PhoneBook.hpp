/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:57:12 by psimcak           #+#    #+#             */
/*   Updated: 2024/08/01 08:19:56 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Agenda.hpp"
#include "Contact.hpp"

class PhoneBook
{
	public:
		Contact	contacts[9];
		int		contact_id;

		PhoneBook( void );
		void initContact(std::string data[5]);
		void addContact(std::string data[5]);
		void searchContact();
		~PhoneBook();
};
