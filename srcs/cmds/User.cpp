#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"

/**
 * @brief Handles the USER command from a user, allowing them to set their
 * username and real name.
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
