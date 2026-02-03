#include "../headers/Server.hpp"
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/* ───────────────────────── signal handling ───────────────────────── */

static volatile sig_atomic_t	g_stop = 0;

static void	onSigInt(int)
{
	g_stop = 1;
}

/* ───────────────────────── ctor/dtor ───────────────────────── */

Server::Server(int port, const std::string &password)
	: _port(port)
	, _password(password)
	, _creationTime(getCurrentDateTime())
	, _serverName(SERVER_NAME)
	, _serverSocket(-1)
	, _serverAddr()
	, _serverRunning(true)
	, _shuttingDown(false)
	, _users()
	, _channels()
	, _commandMap()
{
	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	INFO("Server created on port " << _port);
}

Server::~Server()
{
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->second)
		{
			close(it->first);
			delete it->second;
		}
	}
	_users.clear();

	for (size_t i = 0; i < _channels.size(); ++i)
		delete _channels[i];
	_channels.clear();

	if (_serverSocket >= 0)
		close(_serverSocket);

	INFO("Server destroyed");
}

/* ───────────────────────── start/run ───────────────────────── */

bool	Server::start()
{
	if (!setupSocket())
		return false;

	initCommandMap();
	return true;
}

void	Server::run()
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, onSigInt);

	while (_serverRunning)
		runLoopOnce();

	INFO("Server exiting");
}

void	ServerController(const std::string &portStr, const std::string &pass)
{
	int port = std::atoi(portStr.c_str());
	if (port <= 0 || port > 65535)
	{
		ERROR("Invalid port (must be 1..65535)");
		return;
	}

	if (isPortInUse(port))
	{
		ERROR("Port " << port << " is already in use");
		return;
	}

	Server s(port, pass);
	if (!s.start())
		return;

	s.run();
}

/* ───────────────────────── socket setup ───────────────────────── */

bool	Server::setupSocket()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket < 0)
	{
		ERROR("socket() failed");
		return false;
	}

	int reuse = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
		ERROR("setsockopt(SO_REUSEADDR) failed");
		return false;
	}

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	_serverAddr.sin_port = htons(static_cast<uint16_t>(_port));

	setNonBlocking(_serverSocket);

	if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
	{
		ERROR("bind() failed");
		return false;
	}

	if (listen(_serverSocket, SOMAXCONN) < 0)
	{
		ERROR("listen() failed");
		return false;
	}

	INFO("Server listening on port " << _port);
	return true;
}

void	Server::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
	{
		ERROR("fcntl(F_GETFL) failed");
		return;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		ERROR("fcntl(F_SETFL, O_NONBLOCK) failed");
}

/* ───────────────────────── poll loop ───────────────────────── */

void	Server::runLoopOnce()
{
	if (g_stop)
		beginShutdown();

	std::vector<struct pollfd> pfds;
	buildPollFds(pfds);

	if (pfds.empty())
	{
		if (_shuttingDown)
			_serverRunning = false;
		return;
	}

	const int timeout = _shuttingDown ? 100 : -1;
	int ret = poll(&pfds[0], pfds.size(), timeout);

	if (ret < 0)
	{
		if (errno == EINTR)
			return;
		ERROR("poll() failed");
		_serverRunning = false;
		return;
	}

	handlePollEvents(pfds, _shuttingDown ? 0 : 1);

	if (_shuttingDown && _users.empty())
		_serverRunning = false;
}

void	Server::buildPollFds(std::vector<struct pollfd> &pfds) const
{
	pfds.clear();
	pfds.reserve(_users.size() + 1);

	if (!_shuttingDown)
	{
		struct pollfd sfd;
		std::memset(&sfd, 0, sizeof(sfd));
		sfd.fd = _serverSocket;
		sfd.events = POLLIN;
		pfds.push_back(sfd);
	}

	for (std::map<int, User*>::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		struct pollfd p;
		std::memset(&p, 0, sizeof(p));
		p.fd = it->first;
		p.events = POLLIN;
		if (it->second && !it->second->outBuffer().empty())
			p.events |= POLLOUT;
		pfds.push_back(p);
	}
}

void	Server::handlePollEvents(const std::vector<struct pollfd> &pfds, size_t userStartIndex)
{
	if (!_shuttingDown && !pfds.empty() && (pfds[0].revents & POLLIN))
		acceptNewUser();

	for (size_t i = userStartIndex; i < pfds.size(); ++i)
	{
		const int fd = pfds[i].fd;

		std::map<int, User*>::iterator it = _users.find(fd);
		if (it == _users.end())
			continue;

		User *u = it->second;

		if (pfds[i].revents & (POLLHUP | POLLERR | POLLNVAL))
		{
			removeUserNow(fd, "Connection error");
			continue;
		}
		if (pfds[i].revents & POLLIN)
			onReadable(u);

		if (_users.find(fd) == _users.end())
			continue;

		if (pfds[i].revents & POLLOUT)
			onWritable(u);
	}
}

/* ───────────────────────── accept / I/O ───────────────────────── */

void	Server::acceptNewUser()
{
	struct sockaddr_in clientAddr;
	socklen_t len = sizeof(clientAddr);

	int fd = accept(_serverSocket, (struct sockaddr*)&clientAddr, &len);
	if (fd < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			ERROR("accept() failed");
		return;
	}

	setNonBlocking(fd);
	_users[fd] = new User(fd, clientAddr);
}

void	Server::onReadable(User *user)
{
	if (!user)
		return;

	const int fd = user->getFd();
	char buf[BUFF_SIZE];

	while (true)
	{
		ssize_t n = recv(fd, buf, sizeof(buf), 0);
		if (n == 0)
		{
			removeUserNow(fd, "Client disconnected");
			return;
		}
		if (n < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			removeUserNow(fd, "recv() failed");
			return;
		}
		user->inBuffer().append(buf, buf + n);
	}

	std::string &in = user->inBuffer();
	while (true)
	{
		size_t nl = in.find('\n');
		if (nl == std::string::npos)
			break;

		std::string line = in.substr(0, nl);
		in.erase(0, nl + 1);

		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty())
			continue;

		Message msg;
		if (!parseIrcLine(line, msg))
			continue;

		dispatch(user, msg);

		if (_users.find(fd) == _users.end())
			return;
		if (user->wantsDisconnect())
			return;
	}
}

void	Server::onWritable(User *user)
{
	if (!user)
		return;

	const int fd = user->getFd();
	std::string &out = user->outBuffer();

	if (out.empty())
	{
		if (user->wantsDisconnect())
			removeUserNow(fd, "Flushed");
		return;
	}

	ssize_t sent = send(fd, out.c_str(), out.size(), 0);
	if (sent < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		removeUserNow(fd, "send() failed");
		return;
	}

	out.erase(0, static_cast<size_t>(sent));
	if (out.empty() && user->wantsDisconnect())
		removeUserNow(fd, "Flushed");
}

/* ───────────────────────── output helpers ───────────────────────── */

void	Server::queueLine(User *user, const std::string &line)
{
	if (!user)
		return;

	std::string out = line;
	if (out.size() < 2 || out.substr(out.size() - 2) != "\r\n")
		out += "\r\n";

	user->outBuffer() += out;
}

void	Server::sendNumeric(User *user, const std::string &code,
							const std::string &middle, const std::string &trailing)
{
	if (!user)
		return;

	const std::string nick = (user->getNickName() == "Unknown") ? "*" : user->getNickName();

	std::string line = ":" + _serverName + " " + code + " " + nick;
	if (!middle.empty())
		line += " " + middle;
	if (!trailing.empty())
		line += " :" + trailing;

	queueLine(user, line);
}

/* ───────────────────────── registration ───────────────────────── */

bool	Server::isPreRegisterCommand(const std::string &cmd)
{
	return (cmd == "PASS" || cmd == "NICK" || cmd == "USER" ||
			cmd == "PING" || cmd == "PONG" || cmd == "QUIT");
}

void	Server::tryRegister(User *user)
{
	if (!user || user->isRegistered())
		return;

	if (!user->passAccepted())
		return;
	if (user->getNickName() == "Unknown")
		return;
	if (user->getUserName() == "Unknown")
		return;

	user->setRegistered(true);

	sendNumeric(user, irc::rpl::WELCOME, "", "Welcome to the IRC server!");
	sendNumeric(user, irc::rpl::YOURHOST, "", "Your host is " + _serverName);
	sendNumeric(user, irc::rpl::CREATED, "", "This server was created " + _creationTime);
	sendNumeric(user, irc::rpl::MYINFO, _serverName + " 1.0 o o", "");
}

/* ───────────────────────── shutdown / cleanup ───────────────────────── */

void	Server::beginShutdown()
{
	if (_shuttingDown)
		return;

	_shuttingDown = true;
	INFO("SIGINT received: graceful shutdown started");

	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->second)
			beginUserDisconnect(it->second, "Server shutting down");
	}
}

void	Server::beginUserDisconnect(User *user, const std::string &reason)
{
	if (!user)
		return;

	queueLine(user, "ERROR :Closing Link: " + reason);
	user->setDisconnectAfterFlush(true);

	detachFromAllChannels(user, reason);
}

void	Server::removeUserNow(int fd, const std::string &reason)
{
	std::map<int, User*>::iterator it = _users.find(fd);
	if (it == _users.end())
		return;

	User *u = it->second;
	if (u)
		detachFromAllChannels(u, reason);

	close(fd);
	delete u;
	_users.erase(it);
}

void	Server::detachFromAllChannels(User *user, const std::string &reason)
{
	if (!user)
		return;

	const std::vector<Channel*> chans = user->getChannels();
	const std::string quitLine = ":" + user->getNickName() + " QUIT :" + reason;

	for (size_t i = 0; i < chans.size(); ++i)
	{
		Channel *ch = chans[i];
		if (!ch)
			continue;

		broadcastToChannel(ch, quitLine, user);

		ch->removeAllReferences(user);
		user->removeChannel(ch);

		deleteChannelIfEmpty(ch);
	}
}

void	Server::deleteChannelIfEmpty(Channel *ch)
{
	if (!ch || !ch->empty())
		return;

	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (*it == ch)
		{
			_channels.erase(it);
			delete ch;
			return;
		}
	}
}

void	Server::broadcastToChannel(Channel *ch, const std::string &line, User *exclude)
{
	if (!ch)
		return;

	const std::vector<User*> &members = ch->users();
	for (size_t i = 0; i < members.size(); ++i)
	{
		User *u = members[i];
		if (!u || u == exclude)
			continue;
		queueLine(u, line);
	}
}

/* ───────────────────────── dispatch ───────────────────────── */

void	Server::initCommandMap()
{
	_commandMap.clear();
	_commandMap["PASS"] = &Server::cmdPass;
	_commandMap["NICK"] = &Server::cmdNick;
	_commandMap["USER"] = &Server::cmdUser;
	_commandMap["PING"] = &Server::cmdPing;
	_commandMap["PONG"] = &Server::cmdPong;
	_commandMap["QUIT"] = &Server::cmdQuit;
	_commandMap["JOIN"] = &Server::cmdJoin;
}

void	Server::dispatch(User *user, const Message &msg)
{
	if (!user)
		return;

	if (!user->isRegistered() && !isPreRegisterCommand(msg.command))
	{
		sendNumeric(user, irc::err::NOTREGISTERED, "", "You have not registered");
		return;
	}

	std::map<std::string, CommandHandler>::iterator it = _commandMap.find(msg.command);
	if (it == _commandMap.end())
	{
		sendNumeric(user, irc::err::UNKNOWNCOMMAND, msg.command, "Unknown command");
		return;
	}

	(this->*(it->second))(user, msg);
}

/* ───────────────────────── channels ───────────────────────── */

Channel*	Server::findChannelByName(const std::string &name)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] && _channels[i]->getName() == name)
			return _channels[i];
	}
	return NULL;
}

Channel*	Server::getOrCreateChannel(const std::string &name)
{
	Channel *ch = findChannelByName(name);
	if (ch)
		return ch;

	ch = new Channel(name);
	_channels.push_back(ch);
	return ch;
}
