#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

static bool	isValidChannelName(const std::string &s)
{
	return (!s.empty() && s[0] == '#');
}

static std::string	buildNamesList(Channel *ch)
{
	std::ostringstream oss;
	const std::vector<User*> &members = ch->users();

	for (size_t i = 0; i < members.size(); ++i)
	{
		User *u = members[i];
		if (!u)
			continue;

		if (i != 0)
			oss << " ";

		if (ch->isOperator(u))
			oss << "@";

		oss << u->getNickName();
	}
	return oss.str();
}

/**
 * @brief Handles the JOIN command from a user, allowing them to join a channel.
 * 
 * JOIN command format:
 * JOIN <#channel>
 * 
 * The user joins the specified channel. If the channel does not exist, it is
 * created. If the user is banned from the channel, they receive an error.
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

	if (ch->isUserBanned(user))
	{
		sendNumeric(user, irc::err::BANNEDFROMCHAN, chanName, "Banned from channel");
		return;
	}

	if (!ch->isUserInChannel(user))
	{
		ch->addUser(user);
		user->addChannel(ch);

		if (ch->users().size() == 1)
			ch->addOperator(user);

		broadcastToChannel(ch, ":" + user->getNickName() + " JOIN :" + chanName, NULL);
	}

	if (ch->getTopic().empty())
		sendNumeric(user, irc::rpl::NOTOPIC, chanName, "No topic is set");
	else
		sendNumeric(user, irc::rpl::TOPIC, chanName, ch->getTopic());

	sendNumeric(user, irc::rpl::NAMREPLY, "= " + chanName, buildNamesList(ch));
	sendNumeric(user, irc::rpl::ENDOFNAMES, chanName, "End of /NAMES list");
}
