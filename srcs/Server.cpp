#include "../headers/Server.hpp"
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/* ──────────────────────────── signal handling ───────────────────────────── */

static volatile sig_atomic_t	g_stop = 0;

static void	onSigInt(int) { g_stop = 1; }

/* ──────────────────────────── Con/Des-tructor ───────────────────────────── */

Server::Server(int port, const std::string &password)
	: _port(port), _password(password)
	, _creationTime(getCurrentDateTime())
	, _serverName(SERVER_NAME)
	, _serverSocket(-1)
	, _serverAddr()
	, _serverRunning(true), _shuttingDown(false)
	, _users(), _channels()
	, _commandMap()
{
	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	INFO("Server created on port " << _port);
}

Server::~Server()
{
	std::map<int, User*>::iterator	it = _users.begin();

	for (; it != _users.end(); ++it)
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


/* ────────────────────────────── command map ─────────────────────────────── */

/**
 * @brief Initializes the command map that associates IRC command strings with
 * their corresponding handler member functions.
 * 
 * This function populates the _commandMap member variable with pairs of
 * command strings and pointers to the corresponding member functions that
 * handle those commands.
 */
void	Server::initCommandMap()
{
	_commandMap.clear();
	_commandMap["PASS"] = &Server::cmdPass;
	_commandMap["NICK"] = &Server::cmdNick;
	_commandMap["USER"] = &Server::cmdUser;

	_commandMap["JOIN"] = &Server::cmdJoin;
	_commandMap["TOPIC"] = &Server::cmdTopic;
	_commandMap["MODE"] = &Server::cmdMode;
	_commandMap["INVITE"] = &Server::cmdInvite;
	_commandMap["KICK"] = &Server::cmdKick;

	_commandMap["PRIVMSG"] = &Server::cmdPrivMsg;

	// extra commands
	_commandMap["QUIT"] = &Server::cmdQuit;
	_commandMap["PART"] = &Server::cmdPart;
	_commandMap["NAMES"] = &Server::cmdNames;
	_commandMap["WHO"] = &Server::cmdWho;
	_commandMap["LIST"] = &Server::cmdList;
	_commandMap["PING"] = &Server::cmdPong;
}

/* ───────────────────────── start/run ───────────────────────── */
/**
 * @brief Starts the server by setting up the socket and initializing the
 * command map.
 * @return True if the server started successfully, false otherwise.
 * 
 * Setting up the server involves creating and binding the server socket,
 * as well as preparing the command map for handling incoming IRC commands.
 */
bool	Server::start()
{
	if (!setupSocket())
		return false;

	initCommandMap();
	return true;
}

/**
 * @brief Runs the main server loop, handling incoming connections and data.
 */
void	Server::run()
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, onSigInt);

	while (_serverRunning)
		runLoopOnce();

	INFO("Server exiting");
}

/**
 * @brief Controller function to initialize and run the server with the
 * specified port and password.
 * This function validates the port number, checks if the port is already in
 * use, and then creates and starts the server instance.
 * 
 * @param portStr The port number as a string to listen on.
 * @param pass The password required for clients to connect to the server.
 */
void	ServerController(const std::string &portStr, const std::string &pass)
{
	int	port = std::atoi(portStr.c_str());

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

/**
 * @brief Sets up the server socket by creating, binding, and listening on it.
 * @return bool True if the socket was set up successfully, false otherwise.
 * 
 * This function creates a TCP socket, sets it to non-blocking mode, binds it to
 * the specified port on all interfaces, and starts listening for incoming
 * connections. If any step fails, it logs an error and returns false.
 */
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
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	{
		ERROR("fcntl(F_SETFL, O_NONBLOCK) failed");
		return;
	}
}

/* ───────────────────────── poll loop ───────────────────────── */

/**
 * @brief Runs one iteration of the server's main loop, handling incoming
 * connections and data.
 * 
 * This function builds the list of file descriptors to poll, calls poll(), and
 * then processes any events that occur on those file descriptors.
 */
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

/**
 * @brief Builds the vector of pollfd structures for the poll() call, including
 * the server socket and all user sockets.
 * @param pfds The vector to be filled with pollfd structures.
 */
void	Server::buildPollFds(std::vector<struct pollfd> &pfds) const
{
	pfds.clear();
	pfds.reserve(_users.size() + 1);

	if (!_shuttingDown)
	{
		struct pollfd	sfd;

		std::memset(&sfd, 0, sizeof(sfd));
		sfd.fd = _serverSocket;
		sfd.events = POLLIN;
		pfds.push_back(sfd);
	}

	std::map<int, User*>::const_iterator	it = _users.begin();
	for (; it != _users.end(); ++it)
	{
		struct	pollfd	p;

		std::memset(&p, 0, sizeof(p));
		p.fd = it->first;
		p.events = POLLIN;
		if (it->second && !it->second->outBuffer().empty())
			p.events |= POLLOUT;
		pfds.push_back(p);
	}
}

/**
 * @brief Handles events from the poll() call, such as new connections and
 * incoming data.
 * @param pfds The vector of pollfd structures returned by poll().
 * @param userStartIndex The index in pfds where user connections start (0 if
 * the server socket is not included, 1 if it is).
 */
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

/**
 * @brief Accepts a new incoming connection on the server socket and adds it to
 * the list of users.
 */
void	Server::acceptNewUser()
{
	struct sockaddr_in	clientAddr;
	socklen_t			len = sizeof(clientAddr);

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

/**
 * @brief Handles readable events on a user socket, reading incoming data and
 * processing complete lines.
 * @param user The User object corresponding to the socket that is readable.
 */
void	Server::onReadable(User *user)
{

	if (!user)
		return;

	const int	fd = user->getFd();
	char		buf[BUFF_SIZE];

	while (true)
	{
		ssize_t	n = recv(fd, buf, sizeof(buf), 0);
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

/**
 * @brief Handles writable events on a user socket, sending any queued output
 * data to the client.
 * @param user The User object corresponding to the socket that is writable.
 */
void	Server::onWritable(User *user)
{
	if (!user)
		return;

	const int	fd = user->getFd();
	std::string	&out = user->outBuffer();

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

/* ───────────────────────────── output helpers ───────────────────────────── */

/**
 * @brief Queues a line to be sent to the user.
 * @param user Pointer to the User object to send the line to.
 * @param line The line to be sent.
 * 
 * This function appends the given line to the user's output buffer, ensuring it
 * ends with the proper IRC line terminators (\r\n).
 */
void	Server::queueLine(User *user, const std::string &line)
{
	if (!user)
		return;

	std::string	out = line;

	if (out.size() < 2 || out.substr(out.size() - 2) != "\r\n")
		out += "\r\n";

	user->outBuffer() += out;
}

/**
 * @brief Sends a numeric reply to the user according to the IRC protocol.
 * @param user Pointer to the User object to send the reply to.
 * @param code The numeric reply code as a string.
 * @param middle The middle parameter of the reply (optional).
 * @param trailing The trailing parameter of the reply (optional).
 * 
 * This function constructs a numeric reply message according to the IRC protocol
 * and queues it for sending to the specified user.
 * 
 * EXAMPLE:
 * To send a welcome message:
 *     sendNumeric(user, "001", "", "Welcome to the IRC server!");
 * This will result in a message like:
 *     :server.name 001 <user-nick> :Welcome to the IRC server!
 */
void	Server::sendNumeric(User *user, const std::string &code,
							const std::string &middle, const std::string &trailing)
{
	if (!user)
		return;

	const std::string	nick = (user->getNickName() == "Unknown") ? "*" : user->getNickName();
	std::string			line = ":" + _serverName + " " + code + " " + nick;

	if (!middle.empty())   { line += " " + middle; }
	if (!trailing.empty()) { line += " :" + trailing; }

	queueLine(user, line);
}

/* ────────────────────────────── registration ────────────────────────────── */

static bool	registrationUncompleted(User *user) {
	return (!user || !user->passAccepted() ||
			user->getNickName() == "Unknown" ||
			user->getUserName() == "Unknown");
}

/**
 * @brief Attempts to register a user if they have completed the necessary
 * registration steps (PASS, NICK, USER).
 * @param user Pointer to the User object to attempt registration for.
 */
void	Server::tryRegister(User *user)
{
	if (!user || user->isRegistered() || registrationUncompleted(user))
		return;

	user->setRegistered(true);

	sendNumeric(user, irc::rpl::WELCOME, "", "Welcome to the IRC server!");
	sendNumeric(user, irc::rpl::YOURHOST, "", "Your host is " + _serverName);
	sendNumeric(user, irc::rpl::CREATED, "", "This server was created " + _creationTime);
	sendNumeric(user, irc::rpl::MYINFO, _serverName + " 1.0 o o", "");
}

/* ─────────────────────────── shutdown / cleanup ─────────────────────────── */

/**
 * @brief Initiates a graceful shutdown of the server, notifying all connected
 * users and preventing new connections.
 */
void	Server::beginShutdown()
{
	if (_shuttingDown)
		return;

	_shuttingDown = true;
	INFO("SIGINT received: graceful shutdown started");

	std::map<int, User*>::iterator	it = _users.begin();
	for (; it != _users.end(); ++it)
		if (it->second)
			beginUserDisconnect(it->second, "Server shutting down");
}

/**
 * @brief Initiates a graceful disconnection of a user, sending a quit message
 * to the user and detaching them from all channels.
 * @param user Pointer to the User object to disconnect.
 * @param reason The reason for disconnection to be sent to the user and other
 * users in the same channels.
 */
void	Server::beginUserDisconnect(User *user, const std::string &reason)
{
	if (!user)
		return;

	queueLine(user, "ERROR :Closing Link: " + reason);
	user->setDisconnectAfterFlush(true);

	detachFromAllChannels(user, reason);
}

/**
 * @brief Immediately removes a user from the server, closing their socket and
 * deleting their User object. This is used for error conditions or when a user
 * needs to be disconnected without waiting for the output buffer to flush.
 * @param fd The file descriptor of the user to remove.
 * @param reason The reason for removal, which will be sent to other users in
 * the same channels.
 */
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

/**
 * @brief Detaches a user from all channels they are currently in, broadcasting
 * a quit message to those channels and removing the user from the channel
 * members list.
 * 
 * This is typically called when a user is disconnecting, to ensure that other
 * users in the same channels are notified and that the server's internal state
 * is cleaned up appropriately.
 * 
 * @param user Pointer to the User object to detach from channels.
 * @param reason The reason for detachment, which will be included in the quit
 * message sent to other users in the same channels.
 */
void	Server::detachFromAllChannels(User *user, const std::string &reason)
{
	if (!user)
		return;

	const std::vector<Channel*> chans = user->getChannels();
	const std::string quitLine = ":" + user->prefix() + " QUIT :" + reason;

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

/**
 * @brief Deletes a channel if it is empty (has no users). This is called after
 * a user leaves a channel or is disconnected, to clean up channels that are no
 * longer in use.
 * @param ch Pointer to the Channel object to check and potentially delete.
 */
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

/**
 * @brief Broadcasts a message to all users in a channel, optionally excluding
 * a specific user (e.g., the sender).
 * @param ch Pointer to the Channel object to broadcast the message to.
 * @param line The message line to send to the channel members.
 * @param exclude Pointer to a User object to exclude from receiving the message,
 * or NULL to send to all members.
 */
void	Server::broadcastToChannel(Channel *ch, const std::string &line, User *exclude)
{
	if (!ch)
		return;

	const std::vector<User*> &members = ch->getUsers();
	for (size_t i = 0; i < members.size(); ++i)
	{
		User *u = members[i];
		if (!u || u == exclude)
			continue;
		queueLine(u, line);
	}
}

/* ──────────────────────────────── dispatch ──────────────────────────────── */

static bool	isPreRegisterCommand(const std::string &cmd)
{
	return (cmd == "PASS" || cmd == "NICK" || cmd == "USER" || cmd == "QUIT"
			|| cmd == "PING" || cmd == "PONG");
}

/**
 * @brief Dispatches an incoming IRC command message to the appropriate handler
 * function based on the command name.
 * @param user Pointer to the User object that sent the command.
 * @param msg The parsed Message object containing the command and parameters.
 * 
 * This function checks if the user is registered before allowing most commands,
 * and then looks up the command in the command map to call the corresponding
 * handler function. If the command is unknown, it sends an error numeric back
 * to the user.
 */
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

User*	Server::findUserByNick(const std::string &nick)
{
	std::map<int, User*>::iterator	it = _users.begin();

	for (; it != _users.end(); ++it)
	{
		User *u = it->second;
		if (u && u->getNickName() == nick)
			return u;
	}
	return NULL;
}

/* ──────────────────────────────── channels ──────────────────────────────── */

Channel*	Server::findChannelByName(const std::string &name)
{
	for (size_t i = 0; i < _channels.size(); ++i)
		if (_channels[i] && _channels[i]->getName() == name)
			return _channels[i];
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
