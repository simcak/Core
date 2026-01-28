#include "../headers/IRC.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/**
 * COMMAND: JOIN
 * PARAMETERS: <channel,channels> [<password>]
 * 
 * JOIN command allows a user to join a channel. If the channel doesn't
 * exist, it gets created.
 * 
 * COMMAND: NAMES
 * PARAMETERS: <channel,channels>
 * 
 * NAMES command command returns a list of all users in a specific
 * channel, which can be requested without joining. 
 * 
 * Validate user
 *  -[X] Does the chanel exist? -> if not create it
 *  -[X] is he in chanel already
 *  -[X] is he banned?
 *  -[ ] does he have a correct password
 *  -[ ] if chanel is invite only is he invited
 *
 *  Once validated 
 *   -[ ] the user recieves list of all the commands that affect the chane 
 *   (including PRIVMSG/NOTICE)
 *   -[ ] send chanel topic
 *   -[ ] send list of all the users including the user joining
 *
 *  Other
 *   -[ ] Handle mutiple channels
 */
void	Server::Cmd_Join(User *user, const std::vector<std::string> &tokens)
{
	Channel	*chan;
	int		i = 1; // we have to iterate through all the chanel
			       // names evetually, so I am using this for 
			       // ease later
	
	if(!user)
	{
		ERROR("handleJoin: User pointer is NULL pointer");
		return;
	}
	
	INFO("User <" << user->getUserName() 
			<< "> trying to join a channel <" 
			<< tokens[1] << ">");
	
	chan = this->findChanelByName(tokens[i]);
	if (!chan)
	{
		DEBG("Channel <" << tokens[i] << "> does not exist. Now Creating");
		chan = new Channel(tokens[i]);
		this->addChannel(chan);
	}

	if (chan->isUserInChanel(user))
	{
		DEBG("User <" << user->getUserName() << "> is in chanel <"
				<< chan->getUserName() <<"> already. Quitting");
		return;
	}
	
	if (chan->isUserBanned(user))
	{
		DEBG("hadnleJoin: User <" << user->getUserName()
				<< "> is banned in chan <" 
				<< chan->getUserName() << ">. Quitting");
		return;
	}

	return;
}

