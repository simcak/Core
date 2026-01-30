#include "User.hpp"
#include "Channel.hpp"

/* ───────────────────────────── Con/Des-tructor ──────────────────────────── */
User::User() :
	_port(0), _fd(-1), _ip("DEFAULT_Hostname"),
	_name("DEFAULT_Name"), _username("Unknown"), _nickname("Unknown"),
	_authenticated(false),
	_inBuffer(), _outBuffer(),
	_disconnected(false),
	_channels()
{
	CST("Default user created");
}

User::User(int fd, const struct sockaddr_in &addr) :
	_port(ntohs(addr.sin_port)), _fd(fd), _ip("UnknownHost"),
	_name("Unknown"), _username("Unknown"), _nickname("Unknown"),
	_authenticated(false),
	_inBuffer(), _outBuffer(),
	_disconnected(false),
	_channels()
{
	char	ipStr[INET_ADDRSTRLEN];

	std::memset(ipStr, 0, sizeof(ipStr));
	inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);
	_ip = ipStr;

	CST("New user connected from " << _ip << ":" << _port << " (FD: " << _fd << ")");
}

User::~User(){ DST("User destroyed"); }

/* ──────────────────────────── member functions ──────────────────────────── */
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
	std::vector<Channel *>::iterator	it = _channels.begin();

	for (; it != _channels.end(); ++it)
	{
		if (*it == ch)
		{
			_channels.erase(it);
			return;
		}
	}
}
