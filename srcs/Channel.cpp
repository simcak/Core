#include "../headers/Channel.hpp"
#include "../headers/User.hpp"

/* ──────────────────────────── Con/Des-tructors ──────────────────────────── */
Channel::Channel(const std::string &name)
	: _name(name)
	, _topic("")
	, _users()
	, _banList()
	, _operators()
	, _invitedUsers()
	, _key("")
	, _inviteOnly(false)
	, _topicProtected(false)
	, _userLimit(0)
{
	INFO("Channel <" << _name << "> created");
}

Channel::~Channel()
{
	INFO("Channel <" << _name << "> destroyed");
}

/* ──────────────────────────────── helpers ───────────────────────────────── */
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

/* ──────────────────────────────── getters ───────────────────────────────── */
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
	// keep operator list consistent
	eraseOne(_operators, user);
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

/* ──────────────────────────────── invites ───────────────────────────────── */
bool Channel::isInvited(User *user) const { return contains(_invitedUsers, user); }

void Channel::addInvited(User *user)
{
	if (!user || isInvited(user))
		return;
	_invitedUsers.push_back(user);
}

void Channel::removeInvited(User *user)
{
	if (!user)
		return;
	eraseOne(_invitedUsers, user);
}

/* ───────────────────────────────── modes ────────────────────────────────── */
const std::string &Channel::getKey() const { return _key; }
void Channel::setKey(const std::string &key) { _key = key; }

bool Channel::inviteOnly() const { return _inviteOnly; }
void Channel::setInviteOnly(bool v) { _inviteOnly = v; }

bool Channel::topicProtected() const { return _topicProtected; }
void Channel::setTopicProtected(bool v) { _topicProtected = v; }

int Channel::userLimit() const { return _userLimit; }
void Channel::setUserLimit(int limit) { _userLimit = (limit < 0 ? 0 : limit); }

std::string Channel::modeString() const
{
	std::string modes = "+";
	std::string params;

	if (_inviteOnly)
		modes += "i";
	if (_topicProtected)
		modes += "t";
	if (!_key.empty())
	{
		modes += "k";
		params += " " + _key;
	}
	if (_userLimit > 0)
	{
		modes += "l";
		std::ostringstream oss;
		oss << _userLimit;
		params += " " + oss.str();
	}

	if (modes == "+")
		return "+";
	return modes + params;
}

void Channel::removeAllReferences(User *user)
{
	if (!user)
		return;
	removeUser(user);
	removeOperator(user);
	unbanUser(user);
	removeInvited(user);
}

bool Channel::empty() const
{
	return _users.empty();
}
