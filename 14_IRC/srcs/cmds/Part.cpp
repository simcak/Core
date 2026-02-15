#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to leave a channel.
 * 
 * FORMAT:
 * PART <channel> [(:)<message>]
 * 
 * EXAMPLES:
 * PART #channel                 <- without message
 * PART #channel :Goodbye!       <- with message
 */
void	Server::cmdPart(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "PART", "Not enough parameters");
		return;
	}

	const std::string &chanName = msg.params[0];
	const std::string partMsg = (msg.params.size() >= 2) ? msg.params[1] : "";
	const std::string &userNick = user->getNickName();

	Channel *ch = findChannelByName(chanName);
	if (!ch)
	{
		sendNumeric(user, irc::err::NOSUCHCHANNEL, chanName, "No such channel");
		return;
	}

	if (!ch->isUserInChannel(user))
	{
		sendNumeric(user, irc::err::NOTONCHANNEL, chanName, "You're not on that channel");
		return;
	}

	std::string line = ":" + user->prefix() + " PART " + userNick + " " + chanName;
	if (!partMsg.empty())
		line += " :" + partMsg;

	broadcastToChannel(ch, line, NULL);

	ch->removeUser(user);
	user->removeChannel(ch);

	deleteChannelIfEmpty(ch);
}
