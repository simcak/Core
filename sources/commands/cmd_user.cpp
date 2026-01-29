#include "../classes/IRC.hpp"
#include "../classes/Server.hpp" //full definition needed
#include "../classes/User.hpp"
#include "../classes/Channel.hpp"

/**
 * Command: USER
 * Parameters: <user> <mode> <unused> <realname>
 * 
 * The USER command in IRC is used during the initial connection
 * to specify a new user's details, including their username and real name.
 */
void	Server::Cmd_User(User *user, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 4)
	{
		sendToUser(user, ":" + _server_name + " 461 * :USER Expects 4 parameters");
		return;
	}

	if (!user->isAuthenticated())
	{
		sendToUser(user, ":" + _server_name + " 451 * :You have not registered (missing PASS)");
		return;
	}

	if (user->getUserName() != "Unknown")
	{
		sendToUser(user, ":" + _server_name + " 462 * :You may not reregister");
		return;
	}

	std::string	username = tokens[0];
	std::string	realname;

	// The real name starts after ':' (typical IRC format)
	for (size_t i = 3; i < tokens.size(); ++i)
	{
		std::string	part = tokens[i];
		if (i == 3 && !part.empty() && part[0] == ':')
			part = part.substr(1);

		if (!realname.empty())
			realname += " ";
		realname += part;
	}

	user->setUserName(username);
	user->setRealName(realname);
	//user->setRegistered(true);

	std::cout << BG "User (fd " << user->getFd() << ") registered with USER: " 
			  << username << " | Real name: " << realname << RST << std::endl;

	sendToUser(user, ":" + _server_name + " 001 " + user->getNickName() + " :Welcome to the IRC server!");
}
