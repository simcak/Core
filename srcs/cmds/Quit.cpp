#include "../../headers/Server.hpp"

/**
 * @brief Handles the QUIT command from a user, allowing them to disconnect
 * from the server with an optional quit message.
 */
void	Server::cmdQuit(User *user, const Message &msg)
{
	if (!user)
		return;

	const std::string reason = msg.params.empty() ? "Quit" : msg.params[0];
	beginUserDisconnect(user, reason);
}
