#include "../headers/Channel.hpp"
#include "../headers/User.hpp"

static bool	contains(const std::vector<User*> &v, User *u)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] == u)
			return true;
	}
	return false;
}

static void	eraseOne(std::vector<User*> &v, User *u)
{
	for (std::vector<User*>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (*it == u)
		{
			v.erase(it);
			return;
		}
	}
}

Channel::Channel(const std::string &name)
	: _name(name)
	, _topic("")
	, _users()
	, _banList()
	, _operators()
{
	INFO("Channel <" << _name << "> created");
}

Channel::~Channel()
{
	INFO("Channel <" << _name << "> destroyed");
}

const std::string &Channel::getName() const { return _name; }
const std::string &Channel::getTopic() const { return _topic; }
void Channel::setTopic(const std::string &topic) { _topic = topic; }

const std::vector<User*> &Channel::users() const { return _users; }

bool Channel::isUserInChannel(User *user) const { return contains(_users, user); }
bool Channel::isUserBanned(User *user) const { return contains(_banList, user); }
bool Channel::isOperator(User *user) const { return contains(_operators, user); }

void Channel::addUser(User *user)
{
	if (!user || isUserInChannel(user))
		return;
	_users.push_back(user);
}

void Channel::removeUser(User *user)
{
	if (!user)
		return;
	eraseOne(_users, user);
}

void Channel::addOperator(User *user)
{
	if (!user || isOperator(user))
		return;
	_operators.push_back(user);
}

void Channel::removeOperator(User *user)
{
	if (!user)
		return;
	eraseOne(_operators, user);
}

void Channel::banUser(User *user)
{
	if (!user || isUserBanned(user))
		return;
	_banList.push_back(user);
}

void Channel::unbanUser(User *user)
{
	if (!user)
		return;
	eraseOne(_banList, user);
}

void Channel::removeAllReferences(User *user)
{
	if (!user)
		return;
	removeUser(user);
	removeOperator(user);
	unbanUser(user);
}

bool Channel::empty() const
{
	return _users.empty();
}
