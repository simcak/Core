#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/////////////////////////////// helper functions ///////////////////////////////
static bool	isValidPositiveInt(const std::string &s)
{
	if (s.empty())
		return false;
	for (size_t i = 0; i < s.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;

	int v = std::atoi(s.c_str());
	return (v > 0);
}

static void	appendMode(std::string &outModes, char &lastSign, bool adding, char modeChar)
{
	char	sign = adding ? '+' : '-';

	if (lastSign != sign)
	{
		outModes += sign;
		lastSign = sign;
	}
	outModes += modeChar;
}

/*******************************************************************************
 * @brief
 * MODE command is used to change or view the mode of a channel.
 * Users must be channel operators to change modes.
 * 
 * INCLUDE: [either + (set) or - (unset)]:
 * - i: invite-only
 * - t: topic-protected
 * - k: key (password) protected
 * - o: operator status
 * - l: user limit
 * 
 * FORMAT:
 * MODE <channel> [<modes> [<mode params>]]
 * 
 * EXAMPLES:
 * MODE #channel                  <- queries current modes
 * MODE #channel +/-i             <- sets/unsets invite-only
 * MODE #channel +/-k secretkey   <- sets/removes key
 * MODE #channel +/-o usernick    <- gives/removes operator status
 * MODE #channel + 10             <- sets user limit to 10
 */
void	Server::cmdMode(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.size() < 1)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE", "Not enough parameters");
		return;
	}

	const std::string &chanName = msg.params[0];
	Channel *ch = findChannelByName(chanName);
	if (!ch)
	{
		sendNumeric(user, irc::err::NOSUCHCHANNEL, chanName, "No such channel");
		return;
	}

	// query current modes
	if (msg.params.size() == 1)
	{
		sendNumeric(user, irc::rpl::CHANNELMODEIS, chanName + " " + ch->modeString(), "");
		return;
	}

	// must be in channel + operator
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

	const std::string	&modeStr = msg.params[1];
	size_t				paramIndex = 2;

	bool				adding = true;
	std::string			outModes;
	std::string			outParams;
	char				lastSign = 0;

	for (size_t i = 0; i < modeStr.size(); ++i)
	{
		char c = modeStr[i];
		if (c == '+') { adding = true; continue; }
		if (c == '-') { adding = false; continue; }

		switch (c)
		{
			case 'i':
				ch->setInviteOnly(adding);
				appendMode(outModes, lastSign, adding, 'i');
				break;

			case 't':
				ch->setTopicLock(adding);
				appendMode(outModes, lastSign, adding, 't');
				break;

			case 'k':
				if (adding)
				{
					if (paramIndex >= msg.params.size())
					{
						sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE", "Not enough parameters");
						return;
					}
					const std::string key = msg.params[paramIndex++];
					ch->setKey(key);
					appendMode(outModes, lastSign, adding, 'k');
					outParams += " " + key;
				}
				else
				{
					ch->setKey("");
					appendMode(outModes, lastSign, adding, 'k');
				}
				break;

			case 'o':
			{
				if (paramIndex >= msg.params.size())
				{
					sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE", "Not enough parameters");
					return;
				}
				const std::string targetNick = msg.params[paramIndex++];
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

				if (adding) ch->addOperator(target);
				else        ch->removeOperator(target);

				appendMode(outModes, lastSign, adding, 'o');
				outParams += " " + targetNick;
				break;
			}

			case 'l':
				if (adding)
				{
					if (paramIndex >= msg.params.size())
					{
						sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE", "Not enough parameters");
						return;
					}
					const std::string limitStr = msg.params[paramIndex++];
					if (!isValidPositiveInt(limitStr))
					{
						sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE", "Invalid limit");
						return;
					}
					ch->setUserLimit(std::atoi(limitStr.c_str()));
					appendMode(outModes, lastSign, adding, 'l');
					outParams += " " + limitStr;
				}
				else
				{
					ch->setUserLimit(0);
					appendMode(outModes, lastSign, adding, 'l');
				}
				break;

			default:
				sendNumeric(user, irc::err::UNKNOWNMODE, std::string(1, c), "is unknown mode char to me");
				break;
		}
	}

	if (!outModes.empty())
	{
		const std::string line = ":" + user->prefix() + " MODE " + chanName + " " + outModes + outParams;
		broadcastToChannel(ch, line, NULL);
	}
}
