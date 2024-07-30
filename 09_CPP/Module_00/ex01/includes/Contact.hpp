/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:56:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/30 15:58:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class Contact
{
private:
	std::string first_name;
	std::string last_name;
	std::string nickname;
public:
	Contact(/* args */);
	~Contact();
};

Contact::Contact(/* args */)
{
}

Contact::~Contact()
{
}
