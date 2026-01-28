
#include "../headers/IRC.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

//tHE SERVER GOT PING, THIS FUNCTION SENDS PONG AS A REPONSE TO TRHE CLINET
// response to PING command
void Server::Cmd_Pong(User *user, const std::vector<std::string> &tokens)
{
    (void) tokens; // Unused parameter
    sendToUser(user, "PONG " + _server_name + "\r\n");
}
