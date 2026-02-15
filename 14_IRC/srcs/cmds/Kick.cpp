#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to kick another user from a channel.
 * 
 * FORMAT:
 * KICK <channel> <user> [<reason>]
 * 
 * EXAMPLES:
 * KICK #channel john :Spamming with fake news
 */
void	Server::cmdKick(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 2)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "KICK", "Not enough parameters");
		return;
	}

	const std::string &chanName = msg.params[0];
	const std::string &targetNick = msg.params[1];
	const std::string reason = (msg.params.size() >= 3) ? msg.params[2] : user->getNickName();

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

	if (!ch->isOperator(user))
	{
		sendNumeric(user, irc::err::CHANOPRIVSNEEDED, chanName, "You're not channel operator");
		return;
	}

	User *target = findUserByNick(targetNick);
	if (!target)
	{
		sendNumeric(user, irc::err::NOSUCHNICK, targetNick, "No such nick/channel");
		return;
	}

	if (!ch->isUserInChannel(target))
	{
		sendNumeric(user, irc::err::USERNOTINCHANNEL, targetNick + " " + chanName, "They aren't on that channel");
		return;
	}

	const std::string kickLine = ":" + user->prefix() + " KICK " + chanName + " " + targetNick + " :" + reason;
	broadcastToChannel(ch, kickLine, NULL);

	ch->removeUser(target);
	target->removeChannel(ch);

	deleteChannelIfEmpty(ch);
}
