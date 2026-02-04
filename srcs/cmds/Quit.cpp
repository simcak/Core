#include "../../headers/Server.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to quit the server with an optional quit message.
 * 
 * FORMAT:
 * QUIT [<reason>]
 * 
 * EXAMPLES:
 * QUIT                        <- quits with default reason "Quit"
 * QUIT :Gone to have lunch    <- quits with reason "Gone to have lunch"
 */
void	Server::cmdQuit(User *user, const Message &msg)
{
	if (!user)
		return;

	const std::string reason = msg.params.empty() ? "Quit" : msg.params[0];
	beginUserDisconnect(user, reason);
}
