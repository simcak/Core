#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"

/*******************************************************************************
 * @brief
 * Replies to an incoming PING as soon as possible.
 *
 * In IRC, PING/PONG is used to verify that the peer is still reachable.
 * The server MUST answer a PING with a PONG echoing the received token.
 *
 * FORMAT:
 *   PING <token>
 *
 * EXAMPLES:
 *   PING 12345
 *   PING :irc.funet.fi
 */
void	Server::cmdPong(User *user, const Message &msg)
{
	if (!user) return;
	if (msg.params.empty())
	{
		sendNumeric(user, irc::err::NOORIGIN, "", "No origin specified");
		return;
	}
	PONG("Pong sent");
	queueLine(user, "PONG " + msg.params[0]);
}

/*******************************************************************************
 * @brief
 * Handles an incoming PONG.
 *
 * For this ft_irc implementation we do not send periodic server PINGs, so we
 * don't need to track PONG replies. We still accept the command to behave like
 * a normal IRC server and to keep clients happy.
 *
 * FORMAT:
 *   PONG <token>
 *
 * EXAMPLES:
 *   PONG 12345
 */
//void	Server::cmdPong(User*, const Message&) {}
