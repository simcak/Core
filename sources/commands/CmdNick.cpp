#include "../classes/Server.hpp"
#include "../classes/User.hpp"

static bool	isValidNick(const std::string &nick)
{
	if (nick.empty())
		return false;
	for (size_t i = 0; i < nick.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(nick[i]);
		if (!std::isalnum(c) && c != '_' && c != '-' && c != '[' && c != ']')
			return false;
	}
	return true;
}

static bool	isNickInUse(const std::map<int, User*> &users, const std::string &nick)
{
	for (std::map<int, User*>::const_iterator it = users.begin(); it != users.end(); ++it)
		if (it->second && it->second->getNickName() == nick)
			return true;
	return false;
}

void	Server::CmdNick(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		QueueToUser(user, ":" + _serverName + " 431 * :No nickname given");
		return;
	}

	std::string newNick = msg.params[0];

	if (!isValidNick(newNick))
	{
		QueueToUser(user, ":" + _serverName + " 432 * " + newNick + " :Erroneous nickname");
		return;
	}

	if (isNickInUse(_users, newNick))
	{
		QueueToUser(user, ":" + _serverName + " 433 * " + newNick + " :Nickname already in use");
		return;
	}

	// Echo nick change
	if (user->getNickName() != "Unknown")
		QueueToUser(user, ":" + user->getNickName() + " NICK :" + newNick);

	user->setNickName(newNick);
	DEBG("User (fd " << user->getFd() << ") set nickname to '" << newNick << "'");
}
