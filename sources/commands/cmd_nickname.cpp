#include "../headers/IRC.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

bool isValidNick(const std::string &nick)
{
	if (nick.empty())
		return false;
	for (size_t i = 0; i < nick.size(); ++i)
	{
		char c = nick[i];
		if (!std::isalnum(c) && c != '_' && c != '-' && c != '[' && c != ']')
			return false;
	}
	return true;
}

bool Server::isNickInUse(const std::string &nick)
{
	for (size_t i = 0; i < _users.size(); ++i)
	{
		if (_users[i]->getNickName() == nick)
			return true;
	}
	return false;
}


void Server::Cmd_Nick(User *user, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 2)
	{
		sendToUser(user, ":" + _server_name + " 431 * :No nickname given");
		return;
	}

	std::string newNick = tokens[1];

	if (!isValidNick(newNick))
	{
		sendToUser(user, ":" + _server_name + " 432 * " + newNick + " :Erroneous nickname");
		return;
	}

	if (isNickInUse(newNick))
	{
		sendToUser(user, ":" + _server_name + " 433 * " + newNick + " :Nickname already in use");
		return;
	}

	// Optional: if user already had a nickname, broadcast nick change to themselves
	if (user->getNickName() != "Unknown")
		sendToUser(user, ":" + user->getNickName() + " NICK :" + newNick);

	user->setNickName(newNick);

	std::cout << green << "User (fd " << user->getFd() << ") set nickname to '" << newNick << "'" << reset << std::endl;
}
