#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/* ──────────────────────────── Con/Des-tructors ──────────────────────────── */
User::User()
	: _fd(-1) , _ip("0.0.0.0")
	, _realName("Unknown"), _username("Unknown"), _nickname("Unknown")
	, _passAccepted(false), _registered(false), _disconnectAfterFlush(false)
	, _inBuffer(), _outBuffer()
	, _channels()
{}

User::User(int fd, const struct sockaddr_in &addr)
	: _fd(fd), _ip("0.0.0.0")
	, _realName("Unknown"), _username("Unknown"), _nickname("Unknown")
	, _passAccepted(false), _registered(false), _disconnectAfterFlush(false)
	, _inBuffer(), _outBuffer()
	, _channels()
{
	char ipStr[INET_ADDRSTRLEN];

	std::memset(ipStr, 0, sizeof(ipStr));
	inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);
	_ip = ipStr;

	INFO("New user connected from " << _ip << " (fd " << _fd << ")");
}

User::~User() { DEBG("User destroyed (fd " << _fd << ")"); }

/* ──────────────────────────── member functions ──────────────────────────── */
std::string	User::prefix() const
{
	const std::string	nick = (_nickname == "Unknown") ? "*" : _nickname;
	const std::string	usr  = (_username == "Unknown") ? "unknown" : _username;

	return (nick + "!~" + usr + "@" + _ip);
}

void	User::addChannel(Channel *ch)
{
	if (!ch)
		return;

	for (size_t i = 0; i < _channels.size(); ++i)
		if (_channels[i] == ch)
			return;

	_channels.push_back(ch);
}

void	User::removeChannel(Channel *ch)
{
	std::vector<Channel*>::iterator	it = _channels.begin();

	for (; it != _channels.end(); ++it)
	{
		if (*it == ch)
		{
			_channels.erase(it);
			return;
		}
	}
}
