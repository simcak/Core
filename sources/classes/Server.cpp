#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"

/* ─────────────────────────── signal handling ────────────────────────────── */
static volatile sig_atomic_t	g_stop = 0;

static void	signalController(int)
{
	// IMPORTANT: keep handler async-signal-safe (no iostream here)
	g_stop = 1;
}

/* ───────────────────────────── Con/Des-tructor ──────────────────────────── */
Server::Server(int port, const std::string &password) :
	_port(port), _password(password), _creationTime(getCurrentDateTime()),
	_serverName(SERVER_NAME),
	_serverSocket(-1), _serverAddr(), _serverRunning(true),
	_users(), _channels(), _commandMap()
{
	std::memset(&_serverAddr, 0, sizeof(_serverAddr));

	CST("Server created! \t Port: " BG << _port << RST " | Pass: " BG << _password << RST);
}

Server::~Server()
{
	// Close all users
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->second)
		{
			close(it->first);
			delete it->second;
		}
	}
	_users.clear();

	// Delete channels
	for (size_t i = 0; i < _channels.size(); ++i)
		delete _channels[i];
	_channels.clear();

	if (_serverSocket >= 0)
		close(_serverSocket);

	DST("Server destroyed");
}

/* ──────────────────────────── Member functions ──────────────────────────── */
void	Server::SetServer()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket < 0)
	{
		ERROR("Socket creation failed.");
		return;
	}
	std::cout << BM "Socket created" RST << std::endl;

	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	_serverAddr.sin_port = htons(_port);

	InitCommandMap();
}

void	Server::BindServer()
{
	int reuse_option = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse_option, sizeof(reuse_option)) < 0)
	{
		ERROR("setsockopt(SO_REUSEADDR) failed.");
		return;
	}

	SetNonBlocking(_serverSocket);

	if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
	{
		ERROR("bind() failed.");
		return;
	}
	std::cout << BM "Server bound to port " BG << _port << RST << std::endl;
}

void	Server::ListenServer()
{
	if (listen(_serverSocket, SOMAXCONN) < 0)
	{
		ERROR("Failed to listen on socket.");
		return;
	}
	std::cout << BM "Server is up and listening for new connections..." RST << std::endl;
}

void	Server::RunServer()
{
	signal(SIGINT, signalController);

	while (_serverRunning)
	{
		if (g_stop)
		{
			INFO("SIGINT received: stopping server loop");
			StopServer();
			break;
		}

		// Build poll list
		std::vector<struct pollfd> pfds;
		pfds.reserve(_users.size() + 1);

		struct pollfd sfd;
		std::memset(&sfd, 0, sizeof(sfd));
		sfd.fd = _serverSocket;
		sfd.events = POLLIN;
		pfds.push_back(sfd);

		for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
		{
			struct pollfd p;
			std::memset(&p, 0, sizeof(p));
			p.fd = it->first;
			p.events = POLLIN;
			if (it->second && !it->second->outBuffer().empty())
				p.events |= POLLOUT;
			pfds.push_back(p);
		}

		int ret = poll(&pfds[0], pfds.size(), -1);
		if (ret < 0)
		{
			if (errno == EINTR)
				continue;
			ERROR("poll() failed.");
			break;
		}

		// server accept
		if (pfds[0].revents & POLLIN)
			AcceptNewUser();

		// users I/O
		for (size_t i = 1; i < pfds.size(); ++i)
		{
			int fd = pfds[i].fd;

			// user might have been removed already
			std::map<int, User*>::iterator it = _users.find(fd);
			if (it == _users.end())
				continue;

			User *u = it->second;

			if (pfds[i].revents & (POLLHUP | POLLERR | POLLNVAL))
			{
				INFO("poll() error/hup: removing fd " << fd);
				RemoveUser(fd);
				continue;
			}
			if (pfds[i].revents & POLLIN)
				OnReadable(u);
			if (_users.find(fd) != _users.end() && (pfds[i].revents & POLLOUT))
				OnWritable(u);
		}
	}

	std::cout << BY "Server shutting down..." RST << std::endl;
}

/* ─────────────────────────── Internal helpers ───────────────────────────── */
void	Server::SetNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
	{
		ERROR("fcntl(F_GETFL) failed.");
		return;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		ERROR("fcntl(F_SETFL, O_NONBLOCK) failed.");
		return;
	}
}

void	Server::InitCommandMap()
{
	_commandMap.clear();

	_commandMap["NICK"] = &Server::CmdNick;
	_commandMap["USER"] = &Server::CmdUser;
	_commandMap["PASS"] = &Server::CmdPass;
	_commandMap["JOIN"] = &Server::CmdJoin;
	_commandMap["PONG"] = &Server::CmdPong;
	_commandMap["QUIT"] = &Server::CmdQuit;

	INFO("Command map initialized");
}

void	Server::AcceptNewUser()
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(client_addr);

	int user_fd = accept(_serverSocket, (struct sockaddr*)&client_addr, &addr_len);
	if (user_fd < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			ERROR("accept() failed.");
		return;
	}

	SetNonBlocking(user_fd);

	User *newUser = new User(user_fd, client_addr);
	_users[user_fd] = newUser;

	INFO("New User connected on fd " << user_fd);
}

void	Server::RemoveUser(int fd)
{
	std::map<int, User*>::iterator it = _users.find(fd);
	if (it == _users.end())
		return;

	User *u = it->second;
	close(fd);
	delete u;

	_users.erase(it);
	INFO("Removed user (fd: " << fd << ")");
}

void	Server::OnReadable(User *user)
{
	if (!user)
		return;

	char tmp[BUFF_SIZE];
	int fd = user->getFd();

	while (true)
	{
		std::memset(tmp, 0, sizeof(tmp));
		ssize_t n = recv(fd, tmp, BUFF_SIZE, 0);

		if (n == 0)
		{
			INFO("User disconnected (fd: " << fd << ")");
			RemoveUser(fd);
			return;
		}
		if (n < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break; // no more data right now
			ERROR("recv() failed, removing user fd " << fd);
			RemoveUser(fd);
			return;
		}

		user->inBuffer().append(tmp, tmp + n);
	}

	// Process complete lines (packet aggregation requirement) :contentReference[oaicite:5]{index=5}
	std::string &in = user->inBuffer();
	while (true)
	{
		size_t pos = in.find('\n');
		if (pos == std::string::npos)
			break;

		std::string line = in.substr(0, pos);
		in.erase(0, pos + 1);

		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty())
			continue;

		Message msg;
		if (!parseIrcLine(line, msg))
			continue;

		Dispatch(user, msg);
	}
}

void	Server::OnWritable(User *user)
{
	if (!user)
		return;

	std::string &buf = user->outBuffer();
	if (buf.empty())
		return;

	int fd = user->getFd();
	ssize_t sent = send(fd, buf.c_str(), buf.size(), 0);
	if (sent < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return; // try again next POLLOUT
		ERROR("send() failed, removing user fd " << fd);
		RemoveUser(fd);
		return;
	}
	buf.erase(0, static_cast<size_t>(sent));
}

void	Server::QueueToUser(User *user, const std::string &msg)
{
	if (!user)
		return;

	std::string out = msg;
	// IRC lines must end in \r\n
	if (out.size() < 2 || out.substr(out.size() - 2) != "\r\n")
		out += "\r\n";

	user->outBuffer() += out;
}

void	Server::Dispatch(User *user, const Message &msg)
{
	std::map<std::string, CommandHandler>::iterator it = _commandMap.find(msg.command);
	if (it != _commandMap.end())
		(this->*(it->second))(user, msg);
	else
		QueueToUser(user, ":" + _serverName + " 421 " + msg.command + " :Unknown command");
}

/* ──────────────────────────── Channels helpers ──────────────────────────── */
Channel	*Server::findChannelByName(const std::string &name)
{
	for (size_t i = 0; i < _channels.size(); ++i)
		if (_channels[i] && _channels[i]->getUserName() == name)
			return _channels[i];
	return NULL;
}

Channel	*Server::getOrCreateChannel(const std::string &name)
{
	Channel *chan = findChannelByName(name);
	if (chan)
		return chan;

	chan = new Channel(name);
	_channels.push_back(chan);
	return chan;
}

/* ──────────────────────────── Global functions ──────────────────────────── */
void	ServerController(std::string const &portStr, std::string const &pass)
{
	int	port = std::atoi(portStr.c_str());

	if (isPortInUse(port))
	{
		ERROR("Port " << port << " is already in use!");
		return;
	}

	Server	server(port, pass);

	server.SetServer();
	server.BindServer();
	server.ListenServer();
	server.RunServer();
}