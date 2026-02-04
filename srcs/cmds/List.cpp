#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/////////////////////////////// helper functions ///////////////////////////////
static std::vector<std::string> splitCommaList(const std::string &s)
{
	std::vector<std::string>	out;
	size_t						pos = 0;

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

static std::string modeInfoForList(Channel *ch)
{
	std::string	modeInfo;

	if (ch->inviteOnly())
		modeInfo += "[+i] ";
	if (!ch->getKey().empty())
		modeInfo += "[+k] ";
	if (ch->userLimit() > 0)
		modeInfo += "[+l] ";
	return modeInfo;
}

/*******************************************************************************
 * @brief
 * Print out all/specific channels on the server along with their topics.
 * 
 * FORMAT:
 * LIST [<channel1,channel2,...>]
 * 
 * EXAMPLES:
 * LIST                      <- lists all channels
 * LIST #channel1,#channel2  <- lists only specified channels
 */
void	Server::cmdList(User *user, const Message &msg)
{
	if (!user)
		return;

	// 321 RPL_LISTSTART: "Channel :Users Name"
	sendNumeric(user, irc::rpl::LISTSTART, "Channel", "Users Name");

	// helper *inside* member context: safe to call private sendNumeric
	// (no C++11 lambda, so just inline the repeated code)
	if (msg.params.empty())
	{
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			Channel *ch = _channels[i];
			if (!ch)
				continue;

			std::ostringstream cnt;
			cnt << ch->users().size();

			const std::string chanName = ch->getName();
			const std::string topic = ch->getTopic();
			const std::string modeInfo = modeInfoForList(ch);

			// 322 RPL_LIST: <channel> <# visible> :<topic>
			sendNumeric(user, irc::rpl::LIST, chanName + " " + cnt.str(), modeInfo + topic);
		}
	}
	else
	{
		const std::vector<std::string> chans = splitCommaList(msg.params[0]);
		for (size_t i = 0; i < chans.size(); ++i)
		{
			Channel *ch = findChannelByName(chans[i]);
			if (!ch)
				continue;

			std::ostringstream cnt;
			cnt << ch->users().size();

			const std::string chanName = ch->getName();
			const std::string topic = ch->getTopic();
			const std::string modeInfo = modeInfoForList(ch);

			sendNumeric(user, irc::rpl::LIST, chanName + " " + cnt.str(), modeInfo + topic);
		}
	}

	// 323 RPL_LISTEND
	sendNumeric(user, irc::rpl::LISTEND, "", "End of LIST");

	DEBG("User " << user->getNickName() << " requested LIST");
}
