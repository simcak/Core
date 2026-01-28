/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:35 by cberneri          #+#    #+#             */
/*   Updated: 2025/10/20 14:19:24 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_irc.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/*
	Command: PASS
	Parameters: <password>
	
	In IRC, the PASS command is used to set a connection password
	that a client must provide before registering their nickname and user information. 
*/


void Server::Cmd_Pass(User *user, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 2)
	{
		sendToUser(user, ":" + _server_name + " 461 * PASS :Not enough parameters");
		return;
	}

	// Check if password already provided
	if (user->isAuthenticated())
	{
		sendToUser(user, ":" + _server_name + " 462 * :You cannot register again");
		return;
	}

	std::string providedPass = tokens[1];
	if (providedPass != _password)
	{
		sendToUser(user, ":" + _server_name + " 464 * :Password incorrect");
		return;
	}

	user->setAuthenticated(true);
	sendToUser(user, ":" + _server_name + " NOTICE * :Password accepted");
	std::cout << green << "User (fd " << user->getFd() << ") authenticated successfully." << reset << std::endl;
}
 