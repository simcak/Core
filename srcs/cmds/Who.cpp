#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"
#include "../../headers/Channel.hpp"

/*******************************************************************************
 * @brief
 * Allows a user to query information about users on the SERVER / in a CHANNEL.
 * 
 * Format of RPL_WHOREPLY (352):
 * <channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>
 * H = here, G = gone (away)
 * * = IRC operator
 * @ = channel operator, + = voiced 
 * 
 * FORMAT:
 * WHO <mask>
 * 
 * EXAMPLES:
 * WHO #channel          <- lists users in #channel
 * WHO nickname          <- lists info about user with nickname
 * WHO *                 <- lists all users on the server
 * 
 */
void	Server::cmdWho(User *user, const Message &msg)
{
	if (!user)
		return;

	// WHO with no params: keep minimal
	if (msg.params.empty())
	{
		sendNumeric(user, irc::rpl::ENDOFWHO, "*", "End of WHO list");
		return;
	}

	const std::string mask = msg.params[0];

	// WHO #channel
	if (!mask.empty() && (mask[0] == '#'))
	{
		Channel *ch = findChannelByName(mask);
		if (!ch)
		{
			sendNumeric(user, irc::rpl::ENDOFWHO, mask, "End of WHO list");
			return;
		}

		const std::vector<User*> &members = ch->users();
		for (size_t i = 0; i < members.size(); ++i)
		{
			User *t = members[i];
			if (!t)
				continue;

			std::string flags = "H";
			if (ch->isOperator(t))
				flags += "@";

			// 352: <channel> <user> <host> <server> <nick> <flags> :<hopcount> <real name>
			const std::string middle =
				mask + " " +
				t->getUserName() + " " +
				t->getIP() + " " +
				_serverName + " " +
				t->getNickName() + " " +
				flags;

			sendNumeric(user, irc::rpl::WHOREPLY, middle, "0 " + t->getRealName());
		}

		sendNumeric(user, irc::rpl::ENDOFWHO, mask, "End of WHO list");
		DEBG("User " << user->getNickName() << " WHO " << mask);
		return;
	}

	// WHO *
	if (mask == "*")
	{
		for (std::map<int, User*>::const_iterator it = _users.begin(); it != _users.end(); ++it)
		{
			User *t = it->second;
			if (!t)
				continue;

			const std::string middle =
				"* " +
				t->getUserName() + " " +
				t->getIP() + " " +
				_serverName + " " +
				t->getNickName() + " H";

			sendNumeric(user, irc::rpl::WHOREPLY, middle, "0 " + t->getRealName());
		}

		sendNumeric(user, irc::rpl::ENDOFWHO, "*", "End of WHO list");
		DEBG("User " << user->getNickName() << " WHO *");
		return;
	}

	// WHO <nick>
	User *t = findUserByNick(mask);
	if (t)
	{
		const std::string middle =
			"* " +
			t->getUserName() + " " +
			t->getIP() + " " +
			_serverName + " " +
			t->getNickName() + " H";

		sendNumeric(user, irc::rpl::WHOREPLY, middle, "0 " + t->getRealName());
	}

	sendNumeric(user, irc::rpl::ENDOFWHO, mask, "End of WHO list");
	DEBG("User " << user->getNickName() << " WHO " << mask);
}
