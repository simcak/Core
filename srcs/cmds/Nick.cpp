#include "../../headers/Server.hpp"
#include "../../headers/User.hpp"

static bool	isValidNick(const std::string &nick)
{
	if (nick.empty())
		return false;

	for (size_t i = 0; i < nick.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(nick[i]);
		if (!std::isalnum(c) && c != '_' && c != '-' && c != '[' && c != ']')
			return false;
	}
	return true;
}

static bool	isNickInUseByOther(const std::map<int, User*> &users, const std::string &nick, const User *self)
{
	for (std::map<int, User*>::const_iterator it = users.begin(); it != users.end(); ++it)
	{
		User *u = it->second;
		if (!u || u == self)
			continue;
		if (u->getNickName() == nick)
			return true;
	}
	return false;
}

/**
 * @brief Handles the NICK command from a user, allowing them to set or change
 * their nickname.
 */
void	Server::cmdNick(User *user, const Message &msg)
{
	if (!user)
		return;

	if (msg.params.empty())
	{
		sendNumeric(user, irc::err::NONICKNAMEGIVEN, "", "No nickname given");
		return;
	}

	const std::string &newNick = msg.params[0];
	if (!isValidNick(newNick))
	{
		sendNumeric(user, irc::err::ERRONEUSNICKNAME, newNick, "Erroneous nickname");
		return;
	}

	// do NOT reject your own current nick
	if (isNickInUseByOther(_users, newNick, user))
	{
		sendNumeric(user, irc::err::NICKNAMEINUSE, newNick, "Nickname is already in use");
		return;
	}

	if (user->getNickName() != "Unknown" && user->getNickName() != newNick)
		queueLine(user, ":" + user->getNickName() + " NICK :" + newNick);

	user->setNickName(newNick);
	tryRegister(user);
}
