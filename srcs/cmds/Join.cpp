#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/////////////////////////////// helper functions ///////////////////////////////
static bool	isValidChannelName(const std::string &s)
{
	bool	validPrefix = (!s.empty() && (s[0] == '#' || s[0] == '&' ||
							s[0] == '+' || s[0] == '!'));
	bool	validLength = (s.length() > 1 && s.length() <= 50);
	bool	validChars = true;

	for (size_t i = 0; i < s.size(); ++i)
	{
		unsigned char	c = static_cast<unsigned char>(s[i]);
		if (c == ' ' || c == '\a' || c == ',' || c == ':')
		{
			validChars = false;
			break;
		}
	}
	return (validPrefix && validLength && validChars);
}

static std::string	buildNamesList(Channel *ch)
{
	std::ostringstream oss;
	const std::vector<User*> &members = ch->getUsers();

	for (size_t i = 0; i < members.size(); ++i)
	{
		User *u = members[i];
		if (!u)						continue;
		if (i != 0)					oss << " ";
		if (ch->isOperator(u))		oss << "@";

		oss << u->getNickName();
	}
	return oss.str();
}

/*******************************************************************************
 * @brief
 * Allows a user to join a channel.
 * 
 * FORMAT:
 * JOIN <channel> [<key>]
 * 
 * EXAMPLES:
 * JOIN #channel [secretkey]     <- joins the channel, optionally with a key
 */
void	Server::cmdJoin(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.empty())
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "JOIN", "Not enough parameters");
		return;
	}

	const std::string &chanName = msg.params[0];
	if (!isValidChannelName(chanName))
	{
		sendNumeric(user, irc::err::NOSUCHCHANNEL, chanName, "No such channel");
		return;
	}

	Channel *ch = getOrCreateChannel(chanName);

	if (ch->getUsers().size() >= 1000)
	{
		sendNumeric(user, irc::err::CHANNELISFULL, chanName, "Cannot join channel (server limit of 1000 users)");
		return;
	}

	if (ch->isUserBanned(user))
	{
		sendNumeric(user, irc::err::BANNEDFROMCHAN, chanName, "Banned from channel");
		return;
	}

	if (ch->isUserInChannel(user))
	{
		sendNumeric(user, irc::err::USERONCHANNEL, chanName, "You're already on that channel");
		return;
	}

	// +i invite-only
	if (ch->getInviteOnly() && !ch->isInvited(user))
	{
		sendNumeric(user, irc::err::INVITEONLYCHAN, chanName, "Cannot join channel (+i)");
		return;
	}

	// +k key
	if (!ch->getKey().empty())
	{
		const bool hasKeyParam = (msg.params.size() >= 2);
		if (!hasKeyParam || msg.params[1] != ch->getKey())
		{
			sendNumeric(user, irc::err::BADCHANNELKEY, chanName, "Cannot join channel (+k)");
			return;
		}
	}

	// +l limit
	if (ch->getUserLimit() > 0 && ch->getUsers().size() >= static_cast<size_t>(ch->getUserLimit()))
	{
		sendNumeric(user, irc::err::CHANNELISFULL, chanName, "Cannot join channel (+l)");
		return;
	}

	if (!ch->isUserInChannel(user))
	{
		ch->addUser(user);
		user->addChannel(ch);

		// consume invite once used
		if (ch->getInviteOnly())
			ch->removeInvited(user);

		if (ch->getUsers().size() == 1)
			ch->addOperator(user);

		broadcastToChannel(ch, ":" + user->prefix() + " JOIN :" + chanName, NULL);
	}

	(ch->getTopic().empty()) ?
		sendNumeric(user, irc::rpl::NOTOPIC, chanName, "No topic is set") :
		sendNumeric(user, irc::rpl::TOPIC, chanName, ch->getTopic());

	sendNumeric(user, irc::rpl::NAMREPLY, "= " + chanName, buildNamesList(ch));
	sendNumeric(user, irc::rpl::ENDOFNAMES, chanName, "End of /NAMES list");
}
