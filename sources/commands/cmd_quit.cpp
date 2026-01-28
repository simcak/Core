/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:35 by cberneri          #+#    #+#             */
/*   Updated: 2026/01/20 14:40:46 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_irc.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/*
** QUIT command - Gracefully disconnects a client from the server
** 
** Syntax: QUIT :[quit message]
** 
** Example: QUIT :Goodbye everyone!
**
** This function:
** 1. Sends QUIT message to all channels the user is in
** 2. Removes user from all channels
** 3. Closes the connection
** 4. Cleans up user data
*/

void Server::Cmd_Quit(User *user, const std::vector<std::string> &tokens)
 {
	(void)user; // BORRAR
	(void)tokens; // BORRAR

	/*
	if (!user)
	{
		ERROR("cmdQuit: NULL user pointer");
		return;
	}

	// Extract quit message (default if empty)
	std::string quitMsg = message.empty() ? "Client exited" : message;

	// Remove leading ':' if present
	if (!quitMsg.empty() && quitMsg[0] == ':')
		quitMsg = quitMsg.substr(1);

	INFO("User <" << user->getNickName() << "> is quitting: " << quitMsg);

	// Build the QUIT message to send to other users
	std::string quitNotice = ":" + user->getNickName() + "!" 
							+ user->getUserName() + "@" 
							+ user->getHostname() 
							+ " QUIT :" + quitMsg + "\r\n";

	// Notify all channels this user is in
	std::vector<Channel *> userChannels = user->getChannels(); // You'll need this method
	for (size_t i = 0; i < userChannels.size(); i++)
	{
	// Send quit message to everyone in the channel
		userChannels[i]->broadcastMessage(quitNotice, user);

		// Remove user from channel
		userChannels[i]->removeUser(user);
	}

	// Send ERROR message to the quitting user
	std::string errorMsg = "ERROR :Closing connection: " + quitMsg + "\r\n";
	send(user->getFd(), errorMsg.c_str(), errorMsg.length(), 0);

	// Close the socket
	close(user->getFd());

	// Mark user for removal (don't delete immediately during poll loop)
	user->setDisconnected(true);

	DEBG("User <" << user->getNickName() << "> disconnected successfully");
	*/
}