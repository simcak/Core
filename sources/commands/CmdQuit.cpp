#include "../classes/Server.hpp"
#include "../classes/User.hpp"

void	Server::CmdQuit(User *user, const Message &)
{
	if (!user)
		return;

	int fd = user->getFd();
	QueueToUser(user, "ERROR :Closing Link");
	// actual close happens after POLLOUT flush; simplest is remove now:
	RemoveUser(fd);
}
