#include "Channel.hpp"
#include "User.hpp"

/* ───────────────────────────── Con/Des-tructor ──────────────────────────── */
Channel::Channel(std::string const &name) :
	_name(name), _topic(""), _users(), _banList(), _operators(), _password()
{
	CST("Channel <" << _name << "> has been created");
}

Channel::~Channel() { DST("Channel <" << _name << "> has been destroyed"); }

/* ──────────────────────────── Member functions ──────────────────────────── */
bool	Channel::isUserInChanel(User *user) const
{
	for (size_t i = 0; i < _users.size(); ++i)
		if (_users[i] == user)
			return true;
	return false;
}

bool	Channel::isUserBanned(User *user) const
{
	for (size_t i = 0; i < _banList.size(); ++i)
		if (_banList[i] == user)
			return true;
	return false;
}

Channel	&Channel::addUser(User *user)
{
	if (!user)
		return *this;
	if (!isUserInChanel(user))
		_users.push_back(user);
	return *this;
}

Channel	&Channel::removeUser(User *user)
{
	if (!user)
		return *this;

	std::vector<User *>::iterator	it = _users.begin();
	for (; it != _users.end(); ++it)
	{
		if (*it == user)
		{
			_users.erase(it);
			return *this;
		}
	}
	return *this;
}

Channel	&Channel::banUser(User *user)
{
	if (!user)
		return *this;
	if (!isUserBanned(user))
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
			DEBG("UnBan: found banned user <" << user->getUserName() << ">. Unbanning");
			_banList.erase(it);
			return *this;
		}
	}
	WARN("UnBan: user <" << (user ? user->getUserName() : "NULL") << "> not found in ban list");
	return *this;
}
