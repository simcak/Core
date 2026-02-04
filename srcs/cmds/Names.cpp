#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/////////////////////////////// helper functions ///////////////////////////////
static std::vector<std::string> splitCommaList(const std::string &s)
{
	std::vector<std::string> out;
	size_t pos = 0;

	while (pos < s.size())
	{
		size_t comma = s.find(',', pos);
		if (comma == std::string::npos)
		{
			out.push_back(s.substr(pos));
			break;
		}
		out.push_back(s.substr(pos, comma - pos));
		pos = comma + 1;
	}
	return out;
}

static std::string buildNames(Channel *ch)
{
	std::ostringstream oss;
	const std::vector<User*> &members = ch->users();
	bool first = true;

	for (size_t i = 0; i < members.size(); ++i)
	{
		User *u = members[i];
		if (!u)
			continue;

		if (!first)
			oss << " ";
		first = false;

		if (ch->isOperator(u))
			oss << "@";
		oss << u->getNickName();
	}
	return oss.str();
}

/*******************************************************************************
 * Command: NAMES
 * Parameters: [<channel>{,<channel>}]
 * 
 * The NAMES command is used to list all nicknames that are visible to the user.
 * If a channel parameter is given, only the users in that channel are listed.
 * 
 * Format of RPL_NAMREPLY (353):
 * <symbol> <channel> :<names>
 * symbol: = for public, * for private, @ for secret
 * 
 * Examples:
 *   NAMES
 *   NAMES #channel
 *   NAMES #chan1,#chan2
 */
void	Server::cmdNames(User *user, const Message &msg)
{
	if (!user)
		return;

	// No params: list all channels we track (simple + ok for ft_irc)
	if (msg.params.empty())
	{
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			Channel *ch = _channels[i];
			if (!ch)
				continue;

			const std::string names = buildNames(ch);
			// If empty channel shouldn't exist in your model, but be safe
			if (!names.empty())
				sendNumeric(user, irc::rpl::NAMREPLY, "= " + ch->getName(), names);

			sendNumeric(user, irc::rpl::ENDOFNAMES, ch->getName(), "End of /NAMES list");
		}

		// Traditional end marker for "all names"
		sendNumeric(user, irc::rpl::ENDOFNAMES, "*", "End of /NAMES list");
		DEBG("User " << user->getNickName() << " requested NAMES (all)");
		return;
	}

	// Param: list specific channels (comma-separated)
	const std::vector<std::string> chans = splitCommaList(msg.params[0]);

	for (size_t i = 0; i < chans.size(); ++i)
	{
		const std::string &chanName = chans[i];
		Channel *ch = findChannelByName(chanName);

		if (!ch)
		{
			sendNumeric(user, irc::rpl::ENDOFNAMES, chanName, "End of /NAMES list");
			continue;
		}

		const std::string names = buildNames(ch);
		if (!names.empty())
			sendNumeric(user, irc::rpl::NAMREPLY, "= " + chanName, names);

		sendNumeric(user, irc::rpl::ENDOFNAMES, chanName, "End of /NAMES list");
	}

	DEBG("User " << user->getNickName() << " requested NAMES");
}
