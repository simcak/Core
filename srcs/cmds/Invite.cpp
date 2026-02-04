#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to invite another user to a channel.
 * 
 * FORMAT:
 * INVITE <nickname> <channel>
 * 
 * EXAMPLES:
 * INVITE john #channel
 */
void	Server::cmdInvite(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 2)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "INVITE", "Not enough parameters");
		return;
	}

	const std::string	&targetNick = msg.params[0];
	const std::string	&chanName = msg.params[1];

	User *target = findUserByNick(targetNick);
	if (!target)
	{
		sendNumeric(user, irc::err::NOSUCHNICK, targetNick, "No such nick/channel");
		return;
	}

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

	if (ch->inviteOnly() && !ch->isOperator(user))
	{
		sendNumeric(user, irc::err::CHANOPRIVSNEEDED, chanName, "You're not channel operator");
		return;
	}

	if (ch->isUserInChannel(target))
	{
		sendNumeric(user, irc::err::USERONCHANNEL, targetNick + " " + chanName, "is already on channel");
		return;
	}

	ch->addInvited(target);

	sendNumeric(user, irc::rpl::INVITING, targetNick + " " + chanName, "");

	queueLine(target, ":" + user->prefix() + " INVITE " + targetNick + " :" + chanName);
}
