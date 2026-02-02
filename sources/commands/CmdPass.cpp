#include "../classes/Server.hpp"
#include "../classes/User.hpp"

void	Server::CmdPass(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		QueueToUser(user, ":" + _serverName + " 461 * PASS :Not enough parameters");
		return;
	}
	if (user->isAuthenticated())
	{
		QueueToUser(user, ":" + _serverName + " 462 * :You cannot register again");
		return;
	}

	if (msg.params[0] != _password)
	{
		QueueToUser(user, ":" + _serverName + " 464 * :Password incorrect");
		return;
	}

	user->setAuthenticated(true);
	QueueToUser(user, ":" + _serverName + " NOTICE * :Password accepted");
	DEBG("User (fd " << user->getFd() << ") authenticated successfully.");
}
