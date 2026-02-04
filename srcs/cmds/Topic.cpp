#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/**
 * @brief
 * 
 * TOPIC command format:
 * TOPIC
 */
void	Server::cmdTopic(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "TOPIC", "Not enough parameters");
		return;
	}

	const std::string &chanName = msg.params[0];
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

	// query
	if (msg.params.size() == 1)
	{
		if (ch->getTopic().empty())
			sendNumeric(user, irc::rpl::NOTOPIC, chanName, "No topic is set");
		else
			sendNumeric(user, irc::rpl::TOPIC, chanName, ch->getTopic());
		return;
	}

	// set
	const std::string newTopic = msg.params[1];

	if (ch->topicProtected() && !ch->isOperator(user))
	{
		sendNumeric(user, irc::err::CHANOPRIVSNEEDED, chanName, "You're not channel operator");
		return;
	}

	ch->setTopic(newTopic);

	const std::string line = ":" + user->prefix() + " TOPIC " + chanName + " :" + newTopic;
	broadcastToChannel(ch, line, NULL);
}
