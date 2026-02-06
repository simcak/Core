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

static void	appendMode(std::string &out, char &lastSign, bool adding, char c)
{
	char	sign = adding ? '+' : '-';

	if (lastSign != sign)
	{
		out += sign;
		lastSign = sign;
	}
	out += c;
}

/////////////////////////////// Mode context ///////////////////////////////////
struct Server::ModeCtx
{
	const std::string	&_chName;
	Channel				*_ch;
	const std::string	&_modeStr;
	size_t				_paramIdx;
	bool				_adding;
	std::string			_outModes;
	std::string			_outParams;
	char				_lastSign;

	ModeCtx(const std::string &cName, Channel *channel, const std::string &mStr)
		: _chName(cName)
		, _ch(channel)
		, _modeStr(mStr)
		, _paramIdx(2)
		, _adding(true)
		, _outModes()
		, _outParams()
		, _lastSign(0)
	{}
};

/////////////////////////////// dispatch ///////////////////////////////////////
Server::ModeFn	Server::getModeHandler(char c)
{
	static const ModeDispatch	table[] = {
		{ 'i', &Server::mode_i },
		{ 't', &Server::mode_t },
		{ 'k', &Server::mode_k },
		{ 'o', &Server::mode_o },
		{ 'l', &Server::mode_l },
		{  0 , 0 }
	};

	for (size_t i = 0; table[i].mode != 0; ++i)
		if (table[i].mode == c)
			return table[i].fn;
	return 0;
}

/////////////////////////////// mode handlers //////////////////////////////////
/**
 * @brief Handles the +i (invite-only) channel mode.
 * 
 * When set, only users who are invited can join the channel.
 */
bool	Server::mode_i(Server *srv, User *user, const Message &, ModeCtx &m)
{
	(void)srv;
	(void)user;

	m._ch->setInviteOnly(m._adding);
	appendMode(m._outModes, m._lastSign, m._adding, 'i');
	return false;
}

/**
 * @brief Handles the +t (topic-protected) channel mode.
 * 
 * When set, only channel operators can set the channel topic.
 */
bool	Server::mode_t(Server *srv, User *user, const Message &, ModeCtx &m)
{
	(void)srv;
	(void)user;

	m._ch->setTopicLock(m._adding);
	appendMode(m._outModes, m._lastSign, m._adding, 't');
	return false;
}

/**
 * @brief Handles the +k (key/password) channel mode.
 * 
 * When set, users must provide the correct key to join the channel. The key is
 * stored in the channel object
 * This handler also manages the mode parameter for un/setting the key.
 */
bool	Server::mode_k(Server *srv, User *user, const Message &msg, ModeCtx &m)
{
	if (m._adding)
	{
		if (m._paramIdx >= msg.params.size())
		{
			srv->sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE",
				"Not enough parameters");
			return true;
		}
		const std::string key = msg.params[m._paramIdx++];
		m._ch->setKey(key);
		appendMode(m._outModes, m._lastSign, m._adding, 'k');
		m._outParams += " " + key;
	}
	else
	{
		m._ch->setKey("");
		appendMode(m._outModes, m._lastSign, m._adding, 'k');
	}
	return false;
}

/**
 * @brief Handles the +o (operator status) channel mode.
 * 
 * When set, the specified user is given operator status in the channel. When
 * unset, the specified user has their operator status removed.
 * This handler also checks if the target user exists in the channel.
 */
bool	Server::mode_o(Server *srv, User *user, const Message &msg, ModeCtx &m)
{
	if (m._paramIdx >= msg.params.size())
	{
		srv->sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE",
			"Not enough parameters");
		return true;
	}

	const std::string	targetNick = msg.params[m._paramIdx++];
	User				*target = srv->findUserByNick(targetNick);

	if (!target)
	{
		srv->sendNumeric(user, irc::err::NOSUCHNICK, targetNick,
			"No such nick/channel");
		return true;
	}
	if (!m._ch->isUserInChannel(target))
	{
		srv->sendNumeric(user, irc::err::USERNOTINCHANNEL,
			targetNick + " " + m._chName, "They aren't on that channel");
		return true;
	}

	if (m._adding) m._ch->addOperator(target);
	else          m._ch->removeOperator(target);

	appendMode(m._outModes, m._lastSign, m._adding, 'o');
	m._outParams += " " + targetNick;
	return false;
}

/**
 * @brief Handles the +l (user limit) channel mode.
 * 
 * When set, the channel is limited to a certain number of users. The limit is
 * specified as a parameter when setting the mode. When unset, the user limit is
 * removed.
 */
bool	Server::mode_l(Server *srv, User *user, const Message &msg, ModeCtx &m)
{
	if (m._adding)
	{
		if (m._paramIdx >= msg.params.size())
		{
			srv->sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE",
				"Not enough parameters");
			return true;
		}
		const std::string limitStr = msg.params[m._paramIdx++];
		if (!isValidPositiveInt(limitStr))
		{
			srv->sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE",
				"Invalid limit");
			return true;
		}
		m._ch->setUserLimit(std::atoi(limitStr.c_str()));
		appendMode(m._outModes, m._lastSign, m._adding, 'l');
		m._outParams += " " + limitStr;
	}
	else
	{
		m._ch->setUserLimit(0);
		appendMode(m._outModes, m._lastSign, m._adding, 'l');
	}
	return false;
}

/////////////////////////////// main command ///////////////////////////////////
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
	if (!user)	return;

	if (msg.params.size() < 1)
	{
		sendNumeric(user, irc::err::NEEDMOREPARAMS, "MODE",
			"Not enough parameters");
		return;
	}

	const std::string	&chanName = msg.params[0];
	Channel				*ch = findChannelByName(chanName);

	if (modePreprocess(user, msg, ch, chanName))	return;

	ModeCtx	m(chanName, ch, msg.params[1]);

	for (size_t i = 0; i < m._modeStr.size(); ++i)
	{
		char	c = m._modeStr[i];

		if (c == '+') { m._adding = true;  continue; }
		if (c == '-') { m._adding = false; continue; }

		ModeFn	modeFunctionPtr = getModeHandler(c);
		if (!modeFunctionPtr)
		{
			sendNumeric(user, irc::err::UNKNOWNMODE, std::string(1, c),
				"is unknown mode char to me");
			continue;
		}
		bool	problem = modeFunctionPtr(this, user, msg, m);
		if (problem)	return;
	}

	if (!m._outModes.empty())
	{
		const std::string	line =
			":" + user->prefix() + " MODE " + m._chName +
			" " + m._outModes + m._outParams;
		broadcastToChannel(ch, line, NULL);
	}
}

/**
 * @brief Preprocesses MODE command by checking:
 * 
 * I:   - channel exists
 * II:  - if only channel name is provided, reply with current modes
 * III: - user must be in channel to change modes
 * IV:  - user must be channel operator to change modes
 */
bool	Server::modePreprocess(User *usr, const Message &msg, Channel *ch,
	const std::string &chName)
{
	if (!ch) // channel must exist
	{
		sendNumeric(usr, irc::err::NOSUCHCHANNEL, chName,
			"No such channel");
		return true;
	}
	if (msg.params.size() == 1) // print out the current modes - not an error
	{
		std::string	modeStr = ch->modeString();
		// if (modeStr == "+") modeStr += " (no modes set)"; // should we?
		sendNumeric(usr, irc::rpl::CHANNELMODEIS, chName + " " + modeStr, "");
		return true;
	}
	if (!ch->isUserInChannel(usr)) // user must be in channel
	{
		sendNumeric(usr, irc::err::NOTONCHANNEL, chName,
			"You're not on that channel");
		return true;
	}
	if (!ch->isOperator(usr)) // user must be a channel operator
	{
		sendNumeric(usr, irc::err::CHANOPRIVSNEEDED, chName,
			"You're not a channel operator");
		return true;
	}
	return false;
}
