#include "../classes/Server.hpp"
#include "../classes/User.hpp"

void	Server::CmdPong(User *user, const Message &)
{
	if (!user)
		return;
	QueueToUser(user, "PONG :" + _serverName);
}
