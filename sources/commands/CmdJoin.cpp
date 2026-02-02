#include "../classes/Server.hpp"
#include "../classes/User.hpp"
#include "../classes/Channel.hpp"

void	Server::CmdJoin(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		QueueToUser(user, ":" + _serverName + " 461 " + user->getNickName() + " JOIN :Not enough parameters");
		return;
	}

	std::string chanName = msg.params[0];
	Channel *chan = getOrCreateChannel(chanName);

	if (chan->isUserBanned(user))
	{
		QueueToUser(user, ":" + _serverName + " 474 " + user->getNickName() + " " + chanName + " :Banned from channel");
		return;
	}

	if (!chan->isUserInChanel(user))
	{
		chan->addUser(user);
		user->addChannel(chan);
	}

	// Minimal JOIN echo (you'll expand later with topic/names)
	QueueToUser(user, ":" + user->getNickName() + " JOIN :" + chanName);
}
