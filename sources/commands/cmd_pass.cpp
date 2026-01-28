#include "../headers/IRC.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/**
 * COMMAND: PASS
 * PARAMETERS: <password>
 * 
 * In IRC, the PASS command is used to set a connection password that a client
 * must provide before registering their nickname and user information. 
 */
void	Server::Cmd_Pass(User *user, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 2)
	{
		sendToUser(user, ":" + _server_name + " 461 * PASS :Not enough parameters");
		return;
	}

	// Check if password already provided
	if (user->isAuthenticated())
	{
		sendToUser(user, ":" + _server_name + " 462 * :You cannot register again");
		return;
	}

	std::string	providedPass = tokens[1];

	if (providedPass != _password)
	{
		sendToUser(user, ":" + _server_name + " 464 * :Password incorrect");
		return;
	}

	user->setAuthenticated(true);
	sendToUser(user, ":" + _server_name + " NOTICE * :Password accepted");
	std::cout << BG "User (fd " << user->getFd() << ") authenticated successfully." RST << std::endl;
}
 