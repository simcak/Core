#include "../headers/ft_irc.hpp"
#include "../headers/Channel.hpp"
#include "../headers/User.hpp"

// Checks if user is already in the channel
// If not, adds them to the _users vector
// Returns *this for method chaining
Channel&	Channel::addUser(User *user)
{
	if (!this->isUserInChanel(user))
		_users.push_back(user);
	return *this;
}

// Checks if user is already banned
// If not, adds them to the _banList vector
Channel& Channel::banUser(User *user)
{
	if (!this->isUserBanned(user))
		_banList.push_back(user);
	return *this;
}

Channel& Channel::unBanUser(User *user)
{

	std::vector<User *>::iterator it = _banList.begin();
	while (it != _banList.end())
	{
		if (*it == user)
		{
			DEBG("UnBan: found banned user <" 
					<< (*it)->getUserName()
					<< ">. Unbanning");
			_banList.erase(it);
			return *this;  // Found and removed, exit
		}
		++it;  // Don't forget to increment!
	}
	WARN("UnBan: user <" << user->getUserName() 
			<< "> not found in ban list"); 
	return *this;
}

Channel::~Channel(){
	INFO("Channel <" << _name << "> has been detroyed");
}

std::string	Channel::getUserName() const {
	return _name;
}

std::string	Channel::getTopic() const {
	return _topic;
}

Channel::Channel(std::string const &name) :
    _name(name),
    _topic(""),
    _users(),
    _banList(),		// Added
    _operators(),
    _password(),
    _user_limit(9)
{
	INFO("Channel <" << _name << "> has been created");
}

Channel&		Channel::setTopic(const std::string &topic){
	_topic = topic;
	return (*this);
}

bool Channel::isUserBanned(User *user) const {
	size_t	numOfBanned;
	size_t	i;

	numOfBanned = _banList.size();
	i = 0;

	while(i < numOfBanned)
	{
		if (_banList[i] == user)
			return (true);
		i++;  // FIX: Added increment
	}
	return (false);
}

bool Channel::isUserInChanel(User *user) const {
	size_t	numOfUsers;
	size_t	i;

	numOfUsers = _users.size();
	i = 0;

	while(i < numOfUsers)
	{
		if (_users[i] == user)
			return (true);
		i++;  // FIX: Added increment
	}
	return (false);
}

