#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

User::User()
	: _fd(-1)
	, _ip("0.0.0.0")
	, _realName("Unknown")
	, _username("Unknown")
	, _nickname("Unknown")
	, _passAccepted(false)
	, _registered(false)
	, _disconnectAfterFlush(false)
	, _inBuffer()
	, _outBuffer()
	, _channels()
{
}

User::User(int fd, const struct sockaddr_in &addr)
	: _fd(fd)
	, _ip("0.0.0.0")
	, _realName("Unknown")
	, _username("Unknown")
	, _nickname("Unknown")
	, _passAccepted(false)
	, _registered(false)
	, _disconnectAfterFlush(false)
	, _inBuffer()
	, _outBuffer()
	, _channels()
{
	char ipStr[INET_ADDRSTRLEN];

	std::memset(ipStr, 0, sizeof(ipStr));
	inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);
	_ip = ipStr;

	INFO("New user connected from " << _ip << " (fd " << _fd << ")");
}

User::~User()
{
	DEBG("User destroyed (fd " << _fd << ")");
}

int	User::getFd() const { return _fd; }
const std::string &User::getIP() const { return _ip; }

const std::string &User::getRealName() const { return _realName; }
const std::string &User::getUserName() const { return _username; }
const std::string &User::getNickName() const { return _nickname; }

bool	User::passAccepted() const { return _passAccepted; }
bool	User::isRegistered() const { return _registered; }
bool	User::wantsDisconnect() const { return _disconnectAfterFlush; }

void	User::setRealName(const std::string &real) { _realName = real; }
void	User::setUserName(const std::string &user) { _username = user; }
void	User::setNickName(const std::string &nick) { _nickname = nick; }

void	User::setPassAccepted(bool v) { _passAccepted = v; }
void	User::setRegistered(bool v) { _registered = v; }
void	User::setDisconnectAfterFlush(bool v) { _disconnectAfterFlush = v; }

std::string &User::inBuffer() { return _inBuffer; }
std::string &User::outBuffer() { return _outBuffer; }

const std::vector<Channel*> &User::getChannels() const { return _channels; }

void	User::addChannel(Channel *ch)
{
	if (!ch)
		return;

	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] == ch)
			return;
	}
	_channels.push_back(ch);
}

void	User::removeChannel(Channel *ch)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (*it == ch)
		{
			_channels.erase(it);
			return;
		}
	}
}
