#include "../headers/IRC.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/*
	Command: USER
	Parameters: <user> <mode> <unused> <realname>

	The USER command in IRC is used during the initial connection
	to specify a new user's details, including their username and real name.
*/

void Server::Cmd_User(User *user, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 5){
		sendToUser(user, ":" + _server_name + " 461 * :USER Expects 4 parameters");
		return;
	}

	if (!user->isAuthenticated()){
		sendToUser(user, ":" + _server_name + " 451 * :You have not registered (missing PASS)");
		return;
	}

	if (user->getUserName() != "Unknown"){
		sendToUser(user, ":" + _server_name + " 462 * :You may not reregister");
		return;
	}

	std::string username = tokens[1];
	std::string realname;

	// The real name starts after ':' (typical IRC format)
	for (size_t i = 4; i < tokens.size(); ++i)
	{
		if (i == 4 && tokens[i][0] == ':'){
			realname = tokens[i].substr(1);
		}else{
			if (!realname.empty())
				realname += " ";
			realname += tokens[i];
		}
	}

	user->setUserName(username);
	user->setRealName(realname);
	//user->setRegistered(true);

	std::cout << green << "User (fd " << user->getFd() << ") registered with USER: " 
			  << username << " | Real name: " << realname << reset << std::endl;

	sendToUser(user, ":" + _server_name + " 001 " + user->getNickName() + " :Welcome to the IRC server!");
}
