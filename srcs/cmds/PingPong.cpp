#include "../../headers/Server.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to send a PING command to the server.
 * 
 * That means the server should respond with a PONG command. It is used to test
 * the connection's liveness.
 * 
 * FORMAT:
 * PING <token>
 * 
 * EXAMPLES:
 * PING 12345
 */
void	Server::cmdPing(User *user, const Message &msg)
{
	if (!user)
		return;

	const std::string token = msg.params.empty() ? _serverName : msg.params[0];
	queueLine(user, "PONG :" + token);
}

void	Server::cmdPong(User *, const Message &) { }
