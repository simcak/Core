#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to specify their username and real name.
 * 
 * FORMAT:
 * USER <username> <ip> <servername> :<realname>
 * 
 * EXAMPLES:
 * USER john doe server.com :John Doe
 * USER peta 0 * :Peta Smith
 */
void	Server::cmdUser(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 4)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "USER", "Not enough parameters");
		return;
	}
	if (user->isRegistered() || user->getUserName() != "Unknown")
	{
		sendNumeric(user, irc::err::ALREADYREGISTRED, "", "You may not reregister");
		return;
	}

	user->setUserName(msg.params[0]);
	user->setRealName(msg.params[3]);
	tryRegister(user);
}
