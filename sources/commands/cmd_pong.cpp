#include "../classes/IRC.hpp"
#include "../classes/Server.hpp" //full definition needed
#include "../classes/User.hpp"
#include "../classes/Channel.hpp"

// THE SERVER GOT PING, THIS FUNCTION SENDS PONG AS A REPONSE TO TRHE CLINET
// response to PING command
void	Server::Cmd_Pong(User *user, const std::vector<std::string> &tokens)
{
	(void) tokens; // Unused parameter
	sendToUser(user, "PONG " + _server_name + "\r\n");
}
