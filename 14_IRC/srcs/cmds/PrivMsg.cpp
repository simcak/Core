#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to send a private message to another user or a channel.
 * 
 * FORMAT:
 * PRIVMSG <target> :<message>         <- without :, it takes one parameter
 * 
 * EXAMPLES:
 * PRIVMSG john :Hello there!          <- sends "Hello there!" to user "john"
 * PRIVMSG #channel :Hello everyone!   <- sends "Hello everyone!" to #channel
 */
void	Server::cmdPrivMsg(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		sendNumeric(user, irc::err::NORECIPIENT, "PRIVMSG", "No recipient given (PRIVMSG)");
		return;
	}
	if (msg.params.size() < 2)
	{
		sendNumeric(user, irc::err::NOTEXTTOSEND, "", "No text to send");
		return;
	}

	const std::string &target = msg.params[0];
	const std::string &text = msg.params[1];

	// channel target
	if (!target.empty() && target[0] == '#')
	{
		Channel *ch = findChannelByName(target);
		if (!ch)
		{
			sendNumeric(user, irc::err::NOSUCHCHANNEL, target, "No such channel");
			return;
		}
		if (!ch->isUserInChannel(user))
		{
			sendNumeric(user, irc::err::CANNOTSENDTOCHAN, target, "Cannot send to channel");
			return;
		}

		const std::string line = ":" + user->prefix() + " PRIVMSG " + target + " :" + text;
		broadcastToChannel(ch, line, user);
		return;
	}

	// user target
	User *dst = findUserByNick(target);
	if (!dst)
	{
		sendNumeric(user, irc::err::NOSUCHNICK, target, "No such nick/channel");
		return;
	}

	queueLine(dst, ":" + user->prefix() + " PRIVMSG " + target + " :" + text);
}
