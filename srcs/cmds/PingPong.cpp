#include "../../headers/Server.hpp"

/**
 * @brief Handles the PING command from a user, responding with a PONG.
 * 
 * PING command format:
 * PING <token>
 * 
 * Ping is used to test the connection between the client and server. The server
 * responds with a PONG command, echoing back the token provided by the client.
 */
void	Server::cmdPing(User *user, const Message &msg)
{
	if (!user)
		return;

	const std::string token = msg.params.empty() ? _serverName : msg.params[0];
	queueLine(user, "PONG :" + token);
}

void	Server::cmdPong(User *, const Message &) { }
