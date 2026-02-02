#include "../classes/Server.hpp"
#include "../classes/User.hpp"

void	Server::CmdUser(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 4)
	{
		QueueToUser(user, ":" + _serverName + " 461 * :USER expects 4 parameters");
		return;
	}

	if (!user->isAuthenticated())
	{
		QueueToUser(user, ":" + _serverName + " 451 * :You have not registered (missing PASS)");
		return;
	}

	if (user->getUserName() != "Unknown")
	{
		QueueToUser(user, ":" + _serverName + " 462 * :You may not reregister");
		return;
	}
	
	// USER <user> <mode> <unused> :<realname>
	user->setUserName(msg.params[0]);
	user->setRealName(msg.params[3]);

	DEBG("User (fd " << user->getFd() << ") registered with USER: "
		<< user->getUserName() << " | Real name: "
		<< user->getRealName() << std::endl);

	QueueToUser(user, ":" + _serverName + " 001 " + user->getNickName() + " :Welcome to the IRC server!");
}
