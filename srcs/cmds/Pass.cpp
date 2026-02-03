#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"

void	Server::cmdPass(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.empty())
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "PASS", "Not enough parameters");
		return;
	}
	if (user->isRegistered() || user->passAccepted())
	{
		sendNumeric(user, irc::err::ALREADYREGISTRED, "", "You may not reregister");
		return;
	}
	if (msg.params[0] != _password)
	{
		sendNumeric(user, irc::err::PASSWDMISMATCH, "", "Password incorrect");
		return;
	}

	user->setPassAccepted(true);
	queueLine(user, ":" + _serverName + " NOTICE * :Password accepted");
	tryRegister(user);
}
