#include "../headers/IRC.hpp"
#include "../headers/Channel.hpp"
#include "../headers/User.hpp"
#include "../headers/Server.hpp"


Server::Server(int port, std::string const &password) :
	_port(port),
	_password(password),
	_creation_time(getCurrentDateTime()),
	_server_name(SERVER_NAME),
	_server_socket(-1),
	_server_address(),
	_server_running(true),
	_poll_fds(),
	_users(),
	_user_address_length(sizeof(_server_address))
	//_handler(CommandHandler(this)) // passes pointer to Server
{
	std::memset(&_server_address, 0, sizeof(_server_address)); // clear struct
	std::cout << yellow << "Server created!" << reset << std::endl;
	std::cout << magenta << "Port: "<< green << _port << reset << std::endl;
	std::cout << magenta << "Pass: "<< green << _password << reset << std::endl;
}

Server::~Server(){
	std::cout << yellow << "Server destroyed." << reset << std::endl;
}



void	Server::SetServer()
{
	// Create the socket
	_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_server_socket < 0)
	{
		std::cerr << red << "Error: Socket creation failed." << reset << std::endl;
		return;
	}
	std::cout << magenta << "Socket created" << reset << std::endl;

	// Initialize address
	memset(&_server_address, 0, sizeof(_server_address)); // sets a block of memory to zero
	_server_address.sin_family = AF_INET;
	_server_address.sin_addr.s_addr = INADDR_ANY; // any IPv4 address
	_server_address.sin_port = htons(_port);
	_user_address_length = sizeof(_server_address);


	// Initialize the command map
	InitCommandMap();

}

void	Server::BindServer()
{
	// Enables reusing the same IP address and port immediately after the server restarts (SO_REUSEADDR)
	int reuse_option = 1;
	if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_option, sizeof(reuse_option)) < 0)
	{
		std::cerr << red << "Error: setsockopt(SO_REUSEADDR) failed." << reset << std::endl;
		return;
	}
	
	// Set the socket to non-blocking mode to allow handling multiple clients simultaneously
	SetNonBlocking(_server_socket);

	// Bind the socket to the server’s IP port and address
	if (bind(_server_socket, (struct sockaddr*)&_server_address, sizeof(_server_address)) < 0)
	{
		std::cerr << red << "Error: bind() failed." << reset << std::endl;
		return;
	}

	std::cout << magenta <<  "Server bound to port " << green << _port << reset << std::endl;

}

void	Server::ListenServer()
{
	// Switches the server socket to listening mode, allowing it to accept new client connections.
	// SOMAXCONN defines the maximum number of pending connection requests that can be queued.
	if (listen(_server_socket, SOMAXCONN) < 0)
	{
		std::cerr << red << "Error: Failed to listen on socket." << reset << std::endl;
		return;
	}
	std::cout << magenta <<  "Server is up and listening for new connections..." << green << reset << std::endl;
}

void	Server::BuildPollVector()
{
	_poll_fds.clear(); //**Clears** the existing vector (removes all previous sockets).
	_poll_fds.reserve(_users.size() + 1); //Allocate space for all sockets (server + users) to avoid reallocations.

	// Server socket (Detect new incoming connections)
	struct pollfd server_fd = {};	//	Creates a pollfd for the server’s listening socket.
	server_fd.fd = _server_socket;	
	server_fd.events = POLLIN; 		//POLLIN means “I want to know when this socket is ready to read” — i.e., when a new client is trying to connect.
	_poll_fds.push_back(server_fd);	// Pushes this entry into _poll_fds.

	//After this step, _poll_fds contains: Index 0 → the server socket

	// Client sockets
	// Loops over every connected user to detect messages from users
	for (size_t i = 0; i < _users.size(); ++i)
	{
		struct pollfd user_fd = {};			//For each user, it creates a new `pollfd` entry:
		user_fd.fd = _users[i]->getFd();	//'.fd' = that user’s socket file descriptor. getFd() gives you their socket number.
		user_fd.events = POLLIN;			//'.events' = `POLLIN`, meaning “tell me when the user sends data”
		_poll_fds.push_back(user_fd);		//Adds it to `_poll_fds`
	}


	// works like this:
	// so _poll_fds will be a complete list for poll() to monitor like this:
	// Index 0 → server socket (accept new users)
	// Index 1 → user 1 socket (read incoming messages)
	// Index 2 → user 2 socket
	// ...

	/*
		→  the server socket is just the first element inside _poll_fds.
		→ _users → owns the logical information about each connected user
		→ _poll_fds → temporary technical list used by poll()
		→  built fresh each time in buildPollVector().

		→  _clients tracks who is connected.
 			→  _poll_fds tells poll() what sockets to watch.

		example:
		
			_clients = [ Client(fd=6), Client(fd=8) ]

			_poll_fds = [
				{ fd=4, events=POLLIN },	// server socket → waiting for new connections
				{ fd=6, events=POLLIN },	// client 1 → waiting for messages
				{ fd=8, events=POLLIN }		// client 2 → waiting for messages
			]

	*/
}

void	Server::StopServer(){ _server_running = false; }

void	Server:: SetNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
	{
		std::cerr << red << "Error: fcntl(F_GETFL) failed." << reset << std::endl;
		return;
	}

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		std::cerr << red << "Error: fcntl(F_SETFL, O_NONBLOCK) failed." << reset << std::endl;
		return;
	}
}

/*
When the server detects a new incoming connection, it should:
	- Accept the connection (accept() system call)
	- Create a new Client object
	- Store it in _clients
	- Rebuild the _poll_fds vector (so poll() also monitors this new client)
*/
void	Server::AcceptNewUser(void)
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(client_addr);
	int					user_fd;

	user_fd = accept(_server_socket, (struct sockaddr*)&client_addr, &addr_len);
	if (user_fd < 0)
	{
		std::cerr << red << "Error: Failed to accept a new connection!" << reset << std::endl;
		return;
	}

	// set non-blocking on user socket too
	SetNonBlocking(user_fd);
	
	// Create a new Client object
	User*	newUser = new User(user_fd, client_addr);

	_users.push_back(newUser);
	std::cout << "New User (" << newUser->getUserName() << ") connected on fd " << user_fd << std::endl;
	// Update poll list so we start monitoring this client
	this->BuildPollVector();
}

//remove from _users
void	Server::RemoveUser(User *user)
{
	if (!user)
		return;

	int	fd = user->getFd();

	close(fd);

	// erase pointer from vector
	std::vector<User *>::iterator it = std::find(_users.begin(), _users.end(), user);
	if (it != _users.end())
		_users.erase(it);
	delete user;
	std::cout << yellow << "Removed user (fd: " << fd << ")" << reset << std::endl;
}

static std::vector<std::string>	splitTokens(const std::string &line)
{
	std::vector<std::string>	tokens;
	std::istringstream			iss(line);
	std::string					token;

	while (iss >> token)
		tokens.push_back(token);

	return tokens;
}

// Utility: send a message to the user
void	Server::sendToUser(User *user, const std::string &message)
{
	if (!user)
		return;

	//this message can be deleted
	std::cout << "[SEND to " << user->getNickName() << "]: " << message << std::endl;

	// This prepares the message according to the IRC protocol format, which requires lines to end with \r\n (carriage return + newline).
	// If the message is empty → add \r\n
	// If the message doesn’t already end with a newline → also add \r\n
	std::string	out = message;

	if (out.empty() || out[out.size() - 1] != '\n')
		out += "\r\n";
	send(user->getFd(), out.c_str(), out.size(), 0);
}

/*

void Server::handlePing(User *user, const std::vector<std::string> &tokens) {
	if (tokens.size() >= 2)
		sendToUser(user, "PONG " + tokens[1]);
	else
		sendToUser(user, "PONG :" + _server_name);
}

void Server::handlePong(User *user, const std::vector<std::string> &tokens) {
	sendToUser(user, ":" + _server_name + " NOTICE " +
					(user->getNickname().empty() ? "*" : user->getNickname()) +
					" :PONG received");
}

void Server::handleQuit(User *user, const std::vector<std::string> &tokens) {
	sendToUser(user, ":" + _server_name + " NOTICE * :Goodbye");
	RemoveUser(user); // user pointer becomes invalid
}

void Server::handlePrivMsg(User *user, const std::vector<std::string> &tokens) {
	if (tokens.size() < 3) {
		sendToUser(user, ":" + _server_name + " NOTICE * :PRIVMSG needs target and message");
		return;
	}

	std::string target = tokens[1];
	std::string message;

	if (tokens[2][0] == ':') message = tokens[2].substr(1);
	else message = tokens[2];

	for (size_t i = 3; i < tokens.size(); ++i)
		message += " " + tokens[i];

	bool delivered = false;

	for (size_t i = 0; i < _users.size(); ++i) {
		if (_users[i]->getNickname() == target) {
			sendToUser(_users[i],
				":" + (user->getNickname().empty() ? "anon" : user->getNickname()) +
				" PRIVMSG " + target + " :" + message);
			delivered = true;
			break;
		}
	}

	if (!delivered) {
		if (target == _server_name || target == "server")
			sendToUser(user, ":" + _server_name + " NOTICE " +
							(user->getNickname().empty() ? "*" : user->getNickname()) +
							" :" + message);
		else
			sendToUser(user, ":" + _server_name + " NOTICE " + user->getNickname() +
							" :No such nick/channel");
	}
}
*/


/////// end of COMMANDS


Channel	*Server::findChanelByName(const std::string &name)
{
	std::vector<Channel *>::iterator	it = _channels.begin();

	for(; it != _channels.end(); ++it)
		if((*it)->getUserName() == name)
			return (*it);

	return (NULL);
}

Channel *	Server::addChannel(Channel *chan)
{
	std::vector<Channel *>::iterator	it = _channels.begin();

	for(; it != _channels.end(); ++it)
	{
		if (*it == chan)
		{
			DEBG("Adding channel: <" << chan->getUserName() 
					<< "> already exists");
			return (chan);
		}
	}
	_channels.push_back(chan);
	return (chan);
}


void Server::debugPrintCommands() const
{
	std::map<std::string, CommandHandler>::const_iterator	it = _commandMap.begin();

	std::cout << "[DEBUG] Available commands:" << std::endl;
	for (; it != _commandMap.end(); ++it)
		std::cout << "  - " << it->first << std::endl;
}

void Server::InitCommandMap()
{
	_commandMap.clear();

	_commandMap["NICK"] = &Server::Cmd_Nick;
	_commandMap["USER"] = &Server::Cmd_User;
	_commandMap["PASS"] = &Server::Cmd_Pass;
	_commandMap["JOIN"] = &Server::Cmd_Join;
	//_commandMap["PING"] = &Server::Cmd_Ping;
	_commandMap["PONG"] = &Server::Cmd_Pong;
	_commandMap["QUIT"] = &Server::Cmd_Quit;
	//_commandMap["PRIVMSG"] = &Server::Cmd_PrivMsg;

	INFO("Command map initialized");
}

/*
// ORIGINAL ParseCommand
void Server::ParseCommand(User *user, const std::vector<std::string> &tokens) {
	if (!user || tokens.empty()) return;

	std::string cmd = tokens[0];

	// Strip leading ':' if present (IRC prefix)
	if (cmd[0] == ':' && tokens.size() > 1)
		cmd = tokens[1];

	for (size_t i = 0; i < cmd.size(); ++i)
		cmd[i] = std::toupper(cmd[i]); // optional: normalize command to uppercase

	//Looks up the command in the _commandMap
	std::map<std::string, CommandHandler>::iterator it = _commandMap.find(cmd);
	if (it != _commandMap.end())
		(this->*(it->second))(user, tokens);
	else
		sendToUser(user, ":" + _server_name + " NOTICE * :Unknown command: " + cmd);
}
*/


void Server::ParseCommand(User *user, const std::vector<std::string> &tokens)
{
	if (!user || tokens.empty())
		return;

	size_t	i = 0;

	// Skip prefix if present
	if (tokens[i][0] == ':')
	{
		i++;
		if (i >= tokens.size())
			return; // nothing left after prefix
	}

	std::string	cmd = tokens[i++];

	// Normalize command to uppercase
	for (size_t j = 0; j < cmd.size(); ++j)
		cmd[j] = std::toupper(cmd[j]);

	// Collect parameters
	std::vector<std::string>	params;

	for (; i < tokens.size(); ++i)
		params.push_back(tokens[i]);

	// Find the command in the MAP handler
	std::map<std::string, CommandHandler>::iterator	it = _commandMap.find(cmd);

	if (it != _commandMap.end())
		(this->*(it->second))(user, params); //Call the member function stored in the map, on this Server instance (example: this->cmd_quit(user, tokens);).
	else {
		// Unknown command numeric reply (421)
		sendToUser(user, ":" + _server_name + " 421 " + cmd + " :Unknown command");
		debugPrintCommands();
	}
}


// This lets your server receive text from connected clients.
void Server::HandleClientMessage(User *user) {
	
 	char	buffer[BUFF_SIZE + 1];

	std::memset(buffer, 0, sizeof(buffer));

	//recv reads data from a socket and returns how many bytes were actually received, the structure: recv(int sockfd, void *buffer, size_t length, int flags);
	//bytesReceived receives data from the client’s socket (the connection to the user).
	//It tries to read up to BUF_SIZE bytes of data from that connection and store them inside the buffer array.
	int bytesReceived = recv(user->getFd(), buffer, BUFF_SIZE, 0);
	
	if (bytesReceived <= 0)
	{
		INFO("User disconnected (fd: " << user->getFd() << ")");
		RemoveUser(user);
		return;
	}

	//This takes the bytes you received from the client (buffer) and turns them into a proper C++ string called messagedata.
	std::string	messagedata(buffer, bytesReceived);

	INFO( "Received: <<" << messagedata << ">>~end rcv");

	std::istringstream	stream(messagedata);
	std::string			line;

	while (std::getline(stream, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty()) continue;

		std::vector<std::string> tokens = splitTokens(line);
		if (tokens.empty()) continue;

		ParseCommand(user, tokens);
	}
}







/*
- Rebuilds the list of sockets (buildPollVector()).
- Waits for activity using poll().
- Handles new connections or messages.
- Loops again forever — until the user presses Ctrl+C or you shut down gracefully (execute the command QUIT or EXIT).
*/
void	Server::RunServer()
{
	// run and handle new connections, messages, etc.
	while (_server_running)
	{
		this->BuildPollVector();	// rebuilds the socket list

		int	poll_ret = poll(_poll_fds.data(), _poll_fds.size(), -1);

		if (poll_ret < 0)
		{
			std::cerr << red << "Poll error!" << reset << std::endl;
			break;
		}

		// If the server socket (index 0) is ready, accept new clients
		if (_poll_fds[0].revents & POLLIN)
			AcceptNewUser();	// handle new connection

		// Check if existing clients have sent data
		// starts in 1 because i[0] is the server
		for (size_t i = 1; i < _poll_fds.size(); ++i)
			if (_poll_fds[i].revents & POLLIN)
				HandleClientMessage(_users[i - 1]);
	}
	std::cout << yellow << "Server shutting down..." << reset << std::endl;
}
