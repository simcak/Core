#include "./IRC.hpp"
#include "./Channel.hpp"
#include "./User.hpp"

/* ───────────────────────────── Con/Des-tructor ──────────────────────────── */
Channel::Channel(std::string const &name) :
	_name(name),
	_topic(""),
	_users(),
	_banList(),
	_operators(),
	_password(),
	_user_limit(9)
{
	INFO("Channel <" << _name << "> has been created");
}

Channel::~Channel(){ INFO("Channel <" << _name << "> has been detroyed"); }

/* ───────────────────────────────── Getters ──────────────────────────────── */
std::string	Channel::getUserName() const { return _name; }
std::string	Channel::getTopic() const { return _topic; }

/* ──────────────────────────── Member functions ──────────────────────────── */
bool	Channel::isUserInChanel(User *user) const
{
	size_t	numOfUsers = _users.size();

	for(size_t i = 0; i < numOfUsers; ++i)
		if (_users[i] == user)
			return (true);

	return (false);
}

bool	Channel::isUserBanned(User *user) const {
	size_t	numOfBanned = _banList.size();

	for(size_t i = 0; i < numOfBanned; ++i)
		if (_banList[i] == user)
			return (true);

	return (false);
}

// Checks if user is already in the channel
// If not, adds them to the _users vector
// Returns *this for method chaining
Channel	&Channel::addUser(User *user)
{
	if (!this->isUserInChanel(user))
		_users.push_back(user);
	return *this;
}

Channel	&Channel::setTopic(const std::string &topic)
{
	_topic = topic;
	return (*this);
}

// Checks if user is already banned
// If not, adds them to the _banList vector
Channel	&Channel::banUser(User *user)
{
	if (!this->isUserBanned(user))
		_banList.push_back(user);
	return *this;
}

Channel	&Channel::unBanUser(User *user)
{
	std::vector<User *>::iterator	it = _banList.begin();

	for (; it != _banList.end(); ++it)
	{
		if (*it == user)
		{
			DEBG("UnBan: found banned user <" 
					<< (*it)->getUserName() << ">. Unbanning");
			_banList.erase(it);
			return *this;
		}
	}
	WARN("UnBan: user <" << user->getUserName()  << "> not found in ban list");
	return *this;
}
